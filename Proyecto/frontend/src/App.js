import React, { useState, useEffect, useCallback } from 'react';
import { Pie } from 'react-chartjs-2';
import 'chart.js/auto';
import './App.css';

function App() {
  const [data, setData] = useState([]);
  const [isConnected, setIsConnected] = useState(false);
  const [isLoading, setIsLoading] = useState(true);
  const [error, setError] = useState(null);
  const [totalMemory, setTotalMemory] = useState(0);

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
          const groupedData = groupAndCalculateMemoryUsage(result);
          setData(groupedData);
          const totalMemory = groupedData.reduce((sum, group) => sum + group.total_memory, 0);
          setTotalMemory(totalMemory);
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

  // Función para agrupar los datos por PID y nombre_proceso y calcular la memoria utilizada
  const groupAndCalculateMemoryUsage = (data) => {
    const grouped = {};

    data.forEach((proceso) => {
      const key = `${proceso.pid}-${proceso.nombre_proceso}`;
      if (!grouped[key]) {
        grouped[key] = {
          pid: proceso.pid,
          nombre_proceso: proceso.nombre_proceso,
          total_memory: 0,
          procesos: []
        };
      }

      grouped[key].procesos.push(proceso);

      // Sumar o restar memoria basada en la llamada
      if (proceso.llamada === 'mmap2') {
        grouped[key].total_memory += proceso.tamano_segmento;
      } else if (proceso.llamada === 'munmap') {
        grouped[key].total_memory -= proceso.tamano_segmento;
      }

      // Usar el valor absoluto de la memoria para evitar números negativos
      grouped[key].total_memory = Math.abs(grouped[key].total_memory);
    });

    return Object.values(grouped);
  };

  const generateChartData = () => {
    const labels = data.map((group) => `${group.nombre_proceso} (PID: ${group.pid})`);
    const memoryData = data.map((group) => group.total_memory);
    const backgroundColors = data.map(
      () => `#${Math.floor(Math.random() * 16777215).toString(16)}` // Generar colores aleatorios
    );

    return {
      labels,
      datasets: [
        {
          data: memoryData,
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
            <table>
              <thead>
                <tr>
                  <th>PID</th>
                  <th>Nombre Proceso</th>
                  <th>Memoria Utilizada (bytes)</th>
                  <th>Porcentaje de Memoria Utilizada</th>
                  <th>Llamadas Detalladas</th>
                </tr>
              </thead>
              <tbody>
                {data.map((procesoGroup) => (
                  <tr key={`${procesoGroup.pid}-${procesoGroup.nombre_proceso}`}>
                    <td>{procesoGroup.pid}</td>
                    <td>{procesoGroup.nombre_proceso}</td>
                    <td>{procesoGroup.total_memory}</td>
                    <td>
                      {totalMemory > 0
                        ? `${((procesoGroup.total_memory / totalMemory) * 100).toFixed(2)}%`
                        : '0%'}
                    </td>
                    <td>
                      {procesoGroup.procesos.map((proceso, index) => (
                        <div key={index} style={{ marginBottom: '5px' }}>
                          <strong>{proceso.llamada}</strong>: {proceso.tamano_segmento} bytes at {proceso.fecha_hora_solicitud}
                        </div>
                      ))}
                    </td>
                  </tr>
                ))}
              </tbody>
            </table>
            <div style={{ width: '50%', margin: '20px auto' }}>
              <h2>Memoria Utilizada por Proceso</h2>
              <Pie data={generateChartData()} />
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
