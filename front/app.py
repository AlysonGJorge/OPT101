import serial
from flask import Flask, render_template_string

# Set up serial communication (adjust port and baud rate as needed)
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)

app = Flask(__name__)

@app.route('/')
def index():
    try:
        valueStr = ser.readline().decode().strip()
        if (valueStr == ''):
            value = 0
        else:
            value = int(valueStr)
    except ValueError:
        value = -1
    
    if value == 0:
        status = "Muito Claro"
        brightness = 0
    elif value == 60:
        status = "Claro"
        brightness = (800 - value) * 255 // 300
    elif value == 127:
        status = "Escuro"
        brightness = (500 - value) * 255 // 300 + 128
    elif value == 0:
        status = "Muito Escuro"
        brightness = 255  # Black background, white text
    else:
        status = "Inválido"
        brightness = 0  # Black background, white text
    
    bg_color = f"rgb({brightness},{brightness},{brightness})"
    text_color = "black" if brightness > 128 else "white"

    return render_template_string('''
    <html>
    <head>
        <title>Light Sensor</title>
        <meta http-equiv="refresh" content="1">
        <style>
            body { 
                background-color: {{ bg_color }}; 
                color: {{ text_color }}; 
                text-align: center; 
                font-size: 2em; 
                display: flex;
                justify-content: center;
                align-items: center;
                height: 100vh;
                margin: 0;
            }
        </style>
    </head>
    <body>
        <p>{{ status }}</p>
    </body>
    </html>
    ''', bg_color=bg_color, text_color=text_color, status=status)

if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5000, debug=True)

