from flask import Flask, render_template_string, jsonify

app = Flask(__name__)

@app.route('/')
def index():
    # Render the main HTML page
    return render_template_string(open('index.html').read())

@app.route('/out_put')
def get_sensor_data():
    try:
        # Open and read data from the txt file
        with open('output_log.txt', 'r') as file:
            lines = file.readlines()

        # Parse the data
        timestamps = []
        temperature = []
        humidity = []
        light = []

        for line in lines:
            parts = line.strip().split(', ')
            if len(parts) == 4:
                timestamps.append(parts[0])
                temperature.append(float(parts[1]))
                humidity.append(float(parts[2]))
                light.append(float(parts[3]))

        # Return the data in JSON format
        sensor_data = {
            'timestamps': timestamps,
            'temperature': temperature,
            'humidity': humidity,
            'light': light
        }
        return jsonify(sensor_data)

    except FileNotFoundError:
        return jsonify({'error': 'File not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)