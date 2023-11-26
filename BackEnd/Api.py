from flask import Flask, request, jsonify
from flask_cors import CORS  # Import the CORS extension
import pyodbc

app = Flask(__name__)
CORS(app)  # Enable CORS for all routes


# Configure your SQL Server connection
server = 'LAPTOP-5BUGCH90\SQLEXPRESS'
database = 'Practica5'
username = 'sa'
password = 'leosql'
connection_string = f'DRIVER={{SQL Server}};SERVER={server};DATABASE={database};UID={username};PWD={password}'

@app.route('/api/receive_data', methods=['POST'])
def receive_data():
    try:
        # Get data from the request's JSON body
        data = request.json

        # Process the data
        result = data["SensorValue"]

        # Save the data to the SQL Server database
        save_to_database(data)

        # Return a JSON response
        return jsonify({'success': True, 'result': result})

    except Exception as e:
        # Return an error response if something goes wrong
        return jsonify({'success': False, 'error': str(e)})

@app.route('/api/getSensorValue', methods=['GET'])
def getSensorValue():
    try:
        last_value = get_last_sensor_value()
        if last_value is not None:
            return jsonify({'success': True, 'last_value': last_value})
        else:
            return jsonify({'success': False, 'error': 'Failed to retrieve the  last sensor value'})

    except Exception as e:
        return jsonify({'success': False, 'error': str(e)})

def get_last_sensor_value():
    try:
        connection = pyodbc.connect(connection_string)
        cursor = connection.cursor()

        query = "SELECT TOP 1 Value FROM SensorData ORDER BY DateTime DESC"
        cursor.execute(query)
        result = cursor.fetchone()

        connection.close()

        if result:
            return result.Value
        else:
            return None

    except Exception as e:
        # Handle the exception (e.g., log the error)
        print(f"Error: {str(e)}")
        return None

def save_to_database(data):
    connection = pyodbc.connect(connection_string)
    cursor = connection.cursor()

    query = "INSERT INTO SensorData (Value) VALUES (?)"
    cursor.execute(query, data['SensorValue'])

    connection.commit()
    connection.close()

if __name__ == '__main__':
    # Run the application on localhost:5000
    app.run(host='192.168.10.2', port=5000, debug=True)
    #app.run(debug=True)
