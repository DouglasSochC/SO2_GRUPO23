import React, { useState, useEffect, useCallback } from 'react';
import { Pie } from 'react-chartjs-2';
import 'chart.js/auto';
import './App.css';

function App() {
  const [procesosData, setProcesosData] = useState([]);
  const [memoryData, setMemoryData] = useState([]);
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
      console.log(`Fetching data from ${apiUrl}/memory`); // Debugging
      const responseMemory = await fetch(`${apiUrl}/memory`);
      const memoryData = await responseMemory.json();

      console.log(`Fetching data from ${apiUrl}/procesos`); // Debugging
      const responseProcesos = await fetch(`${apiUrl}/procesos`);
      const procesosData = await responseProcesos.json();

      if (responseMemory.ok && responseProcesos.ok) {
        setMemoryData(memoryData.slice(0, 10)); // Mostrar solo los primeros 10 procesos para la gráfica y la tabla
        setProcesosData(procesosData.slice(0, 50)); // Mostrar las últimas 50 inserciones en la tabla de procesos
        setIsLoading(false);
      } else {
        setError('Failed to fetch data from /memory or /procesos.');
        console.error('Failed to fetch data from /memory or /procesos.');
      }
    } catch (error) {
      setError('Error fetching data from /memory or /procesos.');
      console.error('Error fetching data from /memory or /procesos:', error);
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

  const generateMemoryChartData = () => {
    const labels = memoryData.map((memory) => memory.nombre);
    const memoryValues = memoryData.map((memory) => parseFloat(memory.porcentaje));
    const backgroundColors = memoryData.map(
      () => `#${Math.floor(Math.random() * 16777215).toString(16)}` // Generar colores aleatorios
    );

    return {
      labels,
      datasets: [
        {
          data: memoryValues,
          backgroundColor: backgroundColors,
          hoverBackgroundColor: backgroundColors,
        },
      ],
    };
  };

  return (
    <div className="App">
      <header className="App-header">
        <h1>Proceso Monitor</h1>
        {isLoading && <p>Loading data...</p>}
        {error && <p style={{ color: 'red' }}>{error}</p>}
        {isConnected ? (
          <>
            <div className="table-container">
              <h2>Uso de Memoria</h2>
              <table>
                <thead>
                  <tr>
                    <th>PID</th>
                    <th>Nombre Proceso</th>
                    <th>Uso de Memoria (%)</th>
                  </tr>
                </thead>
                <tbody>
                  {memoryData.map((memory) => (
                    <tr key={memory.pid}>
                      <td>{memory.pid}</td>
                      <td>{memory.nombre}</td>
                      <td>{memory.porcentaje}</td>
                    </tr>
                  ))}
                </tbody>
              </table>
              <div className="chart-container">
                <h2>Gráfica de Uso de Memoria</h2>
                <Pie data={generateMemoryChartData()} />
              </div>
            </div>

            <div className="table-container">
              <h2>Últimas Inserciones de Procesos</h2>
              <table>
                <thead>
                  <tr>
                    <th>ID</th>
                    <th>PID</th>
                    <th>Nombre Proceso</th>
                    <th>Llamada</th>
                    <th>Tamaño Segmento</th>
                    <th>Fecha/Hora Solicitud</th>
                  </tr>
                </thead>
                <tbody>
                  {procesosData.map((proceso) => (
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
            </div>
          </>
        ) : (
          <p>Not connected to the backend</p>
        )}
      </header>
    </div>
  );
}

export default App;
