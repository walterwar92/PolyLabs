import os
import subprocess
import pandas as pd
import matplotlib.pyplot as plt
from flask import Flask, jsonify, request, abort, send_file
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

SCRIPTS_DIR = "/home/scilab_scripts"
OUTPUT_CSV = os.path.join(SCRIPTS_DIR, "output.csv")
# Для графиков зададим отдельные имена
OUTPUT_PNG = os.path.join(SCRIPTS_DIR, "output.png")
OUTPUT_PNG1 = os.path.join(SCRIPTS_DIR, "output1.png")
OUTPUT_PNG2 = os.path.join(SCRIPTS_DIR, "output2.png")

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

        # Построение графиков из CSV
        output_png1 = None
        output_png2 = None
        if os.path.exists(OUTPUT_CSV):
            df = pd.read_csv(OUTPUT_CSV, header=None)
            # Если запускается лабораторная 1 часть 2, т.е. script1_1.sci
            if script_name == "script1_1.sci":
                df.columns = ["t", "rk4", "ode"]
                # Первый график: метод Рунге–Кутта 4-го порядка
                plt.figure()
                plt.plot(df["t"], df["rk4"], "b-")
                plt.xlabel("t")
                plt.ylabel("x1 (RK4)")
                plt.title("Решение ОДУ методом Рунге–Кутта 4-го порядка")
                plt.grid(True)
                plt.savefig(OUTPUT_PNG1)
                output_png1 = OUTPUT_PNG1

                # Второй график: встроенная функция ode
                plt.figure()
                plt.plot(df["t"], df["ode"], "r-")
                plt.xlabel("t")
                plt.ylabel("x1 (ode)")
                plt.title("Решение ОДУ встроенной функцией ode")
                plt.grid(True)
                plt.savefig(OUTPUT_PNG2)
                output_png2 = OUTPUT_PNG2
            else:
                df.columns = ["t", "y"]
                plt.figure()
                plt.plot(df["t"], df["y"], "b-")
                plt.xlabel("t")
                plt.ylabel("y(t)")
                plt.title("Решение ОДУ")
                plt.grid(True)
                plt.savefig(OUTPUT_PNG)
                output_png1 = OUTPUT_PNG

        result_json = {"status": "success", "csv": OUTPUT_CSV}
        if output_png2:
            result_json["image1"] = output_png1
            result_json["image2"] = output_png2
        else:
            result_json["image"] = output_png1

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
