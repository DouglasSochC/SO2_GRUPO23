import React, { useState, useEffect, useCallback } from 'react';
import './App.css';

function App() {
  const [data, setData] = useState([]);
  const [isConnected, setIsConnected] = useState(false);
  const [isLoading, setIsLoading] = useState(true);
  const [error, setError] = useState(null);

  const apiUrl = process.env.REACT_APP_API_URL;

  const checkConnection = useCallback(async () => {
    try {
      const response = await fetch(`${apiUrl}/hello`);
      if (response.ok) {
        setIsConnected(true);
        console.log('Connected to the backend successfully.');
      } else {
        setIsConnected(false);
        console.error('Failed to connect to the backend.');
      }
    } catch (error) {
      setIsConnected(false);
      console.error('Error connecting to the backend:', error);
    }
  }, [apiUrl]);

  const fetchData = useCallback(async () => {
    try {
      console.log(`Fetching data from ${apiUrl}/procesos`); // Depuración
      const response = await fetch(`${apiUrl}/procesos`);
      const text = await response.text();
      console.log('Response text:', text); // Depuración

      if (response.ok) {
        // Intenta analizar el texto como JSON
        try {
          const result = JSON.parse(text);
          setData(result);
          setIsLoading(false);
        } catch (jsonError) {
          setError('Failed to parse JSON');
          console.error('Failed to parse JSON:', jsonError);
          console.log('Response text was:', text);
        }
      } else {
        setError('Failed to fetch data from /procesos.');
        console.error('Failed to fetch data from /procesos.');
      }
    } catch (error) {
      setError('Error fetching data from /procesos.');
      console.error('Error fetching data from /procesos:', error);
    }
  }, [apiUrl]);

  useEffect(() => {
    checkConnection();
  }, [checkConnection]);

  useEffect(() => {
    if (isConnected) {
      fetchData();
      const interval = setInterval(fetchData, 3000);
      return () => clearInterval(interval);
    }
  }, [isConnected, fetchData]);

  return (
    <div className="App">
      <header className="App-header">
        <h1>Proceso Monitor</h1>
        {isLoading && <p>Loading data...</p>}
        {error && <p style={{ color: 'red' }}>{error}</p>}
        {isConnected ? (
          <table>
            <thead>
              <tr>
                <th>ID</th>
                <th>PID</th>
                <th>Nombre Proceso</th>
                <th>Llamada</th>
                <th>Tamaño Segmento</th>
                <th>Fecha Hora Solicitud</th>
              </tr>
            </thead>
            <tbody>
              {data.map((proceso) => (
                <tr key={proceso.id}>
                  <td>{proceso.id}</td>
                  <td>{proceso.pid}</td>
                  <td>{proceso.nombre_proceso}</td>
                  <td>{proceso.llamada}</td>
                  <td>{proceso.tamano_segmento}</td>
                  <td>{proceso.fecha_hora_solicitud}</td>
                </tr>
              ))}
            </tbody>
          </table>
        ) : (
          <p>Not connected to the backend</p>
        )}
      </header>
    </div>
  );
}

export default App;
