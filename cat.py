from flask import Flask, jsonify, request, abort
import os
import subprocess
import base64
import time
from flask_cors import CORS

app = Flask(__name__)
CORS(app)  # Разрешаем CORS для всех маршрутов

# Путь к директории со скриптами Scilab
SCRIPTS_DIR = "/home/scilab_scripts"  # Убедитесь, что этот путь корректный

@app.route('/get_scripts', methods=['GET'])
def get_scripts():
    try:
        scripts = [f for f in os.listdir(SCRIPTS_DIR)
                   if os.path.isfile(os.path.join(SCRIPTS_DIR, f)) and f.lower().endswith(('.sci', '.sce'))]
        return jsonify(scripts)
    except Exception as e:
        return jsonify({"error": str(e)}), 500

@app.route('/script', methods=['GET'])
def get_script():
    filename = request.args.get('filename')
    if not filename:
        abort(400, description="Missing 'filename' parameter")
    
    file_path = os.path.join(SCRIPTS_DIR, filename)
    if not os.path.exists(file_path):
        abort(404, description="File not found")
    
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        return content
    except Exception as e:
        return jsonify({"error": str(e)}), 500

@app.route('/run', methods=['POST'])
def run_script():
    # Принимаем параметры: имя скрипта и шаг (если требуется)
    script_name = request.form.get('script')
    step = request.form.get('step')
    if not script_name:
        abort(400, description="Missing 'script' parameter")
    
    file_path = os.path.join(SCRIPTS_DIR, script_name)
    if not os.path.exists(file_path):
        abort(404, description="Script file not found")
    
    try:
        env = os.environ.copy()
        if step is not None:
            env["STEP"] = step

        # Запускаем Scilab с нужными флагами, устанавливая рабочую директорию
        cmd = ["scilab", "-nwni", "-nb", "-f", file_path]
        result = subprocess.run(cmd, capture_output=True, text=True, env=env, cwd=SCRIPTS_DIR)
        
        # Если произошла ошибка выполнения, возвращаем информацию об ошибке
        if result.returncode != 0:
            return jsonify({"error": "Script execution failed", "details": result.stderr}), 500
        
        # Небольшая задержка, чтобы файлы успели создаться
        time.sleep(1)
        
        # Чтение CSV файла
        csv_file = os.path.join(SCRIPTS_DIR, "output.csv")
        if not os.path.exists(csv_file):
            return jsonify({"error": "CSV file not found after execution"}), 500
        with open(csv_file, "r", encoding="utf-8") as f:
            csv_data = f.read()
        
        # Чтение PNG файла и кодирование в Base64
        png_file = os.path.join(SCRIPTS_DIR, "output.png")
        if not os.path.exists(png_file):
            return jsonify({"error": "PNG file not found after execution"}), 500
        with open(png_file, "rb") as f:
            png_bytes = f.read()
            png_data = base64.b64encode(png_bytes).decode("utf-8")
        
        # Возвращаем данные в JSON с ключами "csv" и "png"
        return jsonify({"csv": csv_data, "png": png_data})
    except Exception as e:
        return jsonify({"error": str(e)}), 500

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')
    if username == "admin" and password == "admin":
        return jsonify({"status": "success"})
    else:
        return jsonify({"status": "error", "message": "Invalid credentials"}), 401

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
