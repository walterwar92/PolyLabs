from flask import Flask, jsonify, request, abort
import os
import subprocess
from flask_cors import CORS

app = Flask(__name__)
CORS(app)  # Разрешаем CORS для всех маршрутов

# Путь к директории со скриптами Scilab
SCRIPTS_DIR = "/home/scilab_scripts"  # Замените на нужный путь

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
    # Принимаем параметры: имя скрипта и шаг
    script_name = request.form.get('script')
    step = request.form.get('step')  # шаг интегрирования, если требуется
    if not script_name:
        abort(400, description="Missing 'script' parameter")
    
    file_path = os.path.join(SCRIPTS_DIR, script_name)
    if not os.path.exists(file_path):
        abort(404, description="Script file not found")
    
    try:
        env = os.environ.copy()
        if step is not None:
            env["STEP"] = step

        # Запускаем Scilab с указанием рабочей директории, где будет создан output.csv
        result = subprocess.run(["scilab", "-nwni", "-nb", "-f", file_path],
                                capture_output=True, text=True, env=env, cwd=SCRIPTS_DIR)
        
        if result.returncode != 0:
            return jsonify({"error": "Script execution failed", "details": result.stderr}), 500

        # Читаем содержимое output.csv, созданного Scilab-скриптом
        output_file = os.path.join(SCRIPTS_DIR, "output.csv")
        if os.path.exists(output_file):
            with open(output_file, "r", encoding="utf-8") as f:
                csv_data = f.read()
        else:
            csv_data = ""
        
        # Возвращаем CSV данные в JSON
        return jsonify({"output": csv_data})
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
    # Запуск приложения на всех интерфейсах, порт 5000
    app.run(host='0.0.0.0', port=5000, debug=True)
