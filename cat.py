import os
import subprocess
import pandas as pd
import matplotlib.pyplot as plt
from flask import Flask, jsonify, request, abort
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

SCRIPTS_DIR = "/home/scilab_scripts"
OUTPUT_CSV = os.path.join(SCRIPTS_DIR, "output.csv")
OUTPUT_PNG = os.path.join(SCRIPTS_DIR, "output.png")

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

        # Запуск Scilab
        result = subprocess.run(["scilab", "-nwni", "-nb", "-f", file_path],
                                capture_output=True, text=True, env=env, cwd=SCRIPTS_DIR)
        
        if result.returncode != 0:
            return jsonify({"error": "Script execution failed", "details": result.stderr}), 500
        
        # Построение графика из CSV
        if os.path.exists(OUTPUT_CSV):
            df = pd.read_csv(OUTPUT_CSV, header=None)
            df.columns = ["t", "y"]

            plt.figure()
            plt.plot(df["t"], df["y"], "b-")
            plt.xlabel("t")
            plt.ylabel("y(t)")
            plt.title("Решение ОДУ методом Адамса-Мултона")
            plt.grid(True)
            plt.savefig(OUTPUT_PNG)
        
        return jsonify({"status": "success", "csv": OUTPUT_CSV, "image": OUTPUT_PNG})
    
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
