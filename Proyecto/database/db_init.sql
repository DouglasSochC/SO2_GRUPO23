-- Crear la base de datos
CREATE DATABASE IF NOT EXISTS proceso_db;

-- Usar la base de datos
USE proceso_db;

-- Crear la tabla para almacenar la información de los procesos
CREATE TABLE IF NOT EXISTS procesos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    pid INT NOT NULL,
    nombre_proceso VARCHAR(255) NOT NULL,
    llamada VARCHAR(50) NOT NULL,
    tamano_segmento INT NOT NULL,
    fecha_hora_solicitud DATETIME
);
