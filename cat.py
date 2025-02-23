import os
import subprocess
import pandas as pd
from flask import Flask, jsonify, request, abort, send_file
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

SCRIPTS_DIR = "/home/scilab_scripts"
OUTPUT_LU_CSV = os.path.join(SCRIPTS_DIR, "LU_result.csv")
OUTPUT_QR_CSV = os.path.join(SCRIPTS_DIR, "QR_result.csv")

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
    script_name = request.form.get('script')
    step = request.form.get('step')

    if not script_name:
        abort(400, description="Missing 'script' parameter")
    
    file_path = os.path.join(SCRIPTS_DIR, script_name)
    if not os.path.exists(file_path):
        abort(404, description="Script file not found")

    try:
        env = os.environ.copy()
        if step:
            env["STEP"] = step

        app.logger.info(f"Running script: {file_path} with step: {step}")

        # Запуск Scilab
        result = subprocess.run(["scilab", "-nwni", "-nb", "-f", file_path],
                                capture_output=True, text=True, env=env, cwd=SCRIPTS_DIR)
        
        if result.returncode != 0:
            app.logger.error(f"Script execution failed: {result.stderr}")
            return jsonify({"error": "Script execution failed", "details": result.stderr}), 500

        app.logger.info("Script executed successfully.")

        # Возврат файлов для скачивания
        result_json = {"status": "success", "LU_csv": OUTPUT_LU_CSV, "QR_csv": OUTPUT_QR_CSV}

        return jsonify(result_json)
    
    except Exception as e:
        app.logger.error(f"Error while running script: {str(e)}")
        return jsonify({"error": str(e)}), 500

@app.route("/download", methods=["GET"])
def download_file():
    file_path = request.args.get("file")
    if not file_path or not os.path.exists(file_path):
        return "Ошибка: файл не найден", 404

    return send_file(file_path, as_attachment=True)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
