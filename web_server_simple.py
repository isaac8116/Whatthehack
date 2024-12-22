from flask import Flask, render_template_string

app = Flask(__name__)

@app.route('/')
def index():
    try:
        with open('output_log.txt', 'r') as file:
            data = file.readlines()
    except FileNotFoundError:
        data = ["No data available."]

    html_template = """
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta http-equiv="refresh" content="5"> <!-- Refresh every 5 seconds -->
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Sensor Data Log</title>
        <style>
            body { font-family: Arial, sans-serif; margin: 40px; }
            pre { background-color: #f4f4f4; padding: 20px; }
        </style>
    </head>
    <body>
        <h1>Sensor Data Log</h1>
        <pre>{{ log_data }}</pre>
    </body>
    </html>
    """

    return render_template_string(html_template, log_data=''.join(data))

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8000, debug=True)