from flask import Flask, jsonify, request, abort
import os
import subprocess
from flask_cors import CORS

app = Flask(__name__)
CORS(app)  # Разрешаем CORS для всех маршрутов

# Задайте путь к директории, где находятся ваши Scilab скрипты
SCRIPTS_DIR = "/home/ubuntu/scilab_scripts"  # Замените на ваш путь

@app.route('/get_scripts', methods=['GET'])
def get_scripts():
    """
    Возвращает список всех файлов с расширениями .sci или .sce в директории SCRIPTS_DIR.
    """
    try:
        # Получаем список файлов в директории, фильтруем по расширению
        scripts = [f for f in os.listdir(SCRIPTS_DIR)
                   if os.path.isfile(os.path.join(SCRIPTS_DIR, f)) and f.lower().endswith(('.sci', '.sce'))]
        return jsonify(scripts)
    except Exception as e:
        return jsonify({"error": str(e)}), 500

@app.route('/script', methods=['GET'])
def get_script():
    """
    Возвращает содержимое выбранного скрипта.
    Ожидает параметр запроса 'filename'
    """
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
    """
    Принимает POST-запрос с параметрами 'script' (имя файла) и 'function' (введённая функция или параметры).
    Запускает Scilab-скрипт и возвращает результат.
    """
    script_name = request.form.get('script')
    function_input = request.form.get('function')  # Может быть пустым
    
    if not script_name:
        abort(400, description="Missing 'script' parameter")
    
    file_path = os.path.join(SCRIPTS_DIR, script_name)
    if not os.path.exists(file_path):
        abort(404, description="Script file not found")
    
    try:
        # Передаём введённую функцию в переменную окружения, чтобы скрипт мог её использовать
        env = os.environ.copy()
        env["FUNCTION_INPUT"] = function_input if function_input is not None else ""
        
        # Запускаем Scilab в безграфическом режиме с указанным скриптом
        result = subprocess.run(["scilab", "-nb", "-f", file_path],
                                capture_output=True, text=True, env=env)
        
        if result.returncode != 0:
            return jsonify({"error": "Script execution failed", "details": result.stderr}), 500
        
        return jsonify({"output": result.stdout})
    except Exception as e:
        return jsonify({"error": str(e)}), 500

@app.route('/login', methods=['POST'])
def login():
    """
    Простой пример проверки логина.
    Ожидает параметры 'username' и 'password'.
    """
    username = request.form.get('username')
    password = request.form.get('password')
    if username == "admin" and password == "admin":
        return jsonify({"status": "success"})
    else:
        return jsonify({"status": "error", "message": "Invalid credentials"}), 401

if __name__ == '__main__':
    # Запуск приложения на всех интерфейсах, порт 5000.
    app.run(host='0.0.0.0', port=5000, debug=True)
