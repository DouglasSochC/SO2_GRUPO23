const Sequelize = require('sequelize');
const db = require('./database.js'); 

const Proceso = db.define('proceso', {
    id: {
        type: Sequelize.INTEGER,
        primaryKey: true,
        autoIncrement: true
    },
    pid: {
        type: Sequelize.INTEGER,
        allowNull: false
    },
    nombre_proceso: {
        type: Sequelize.STRING(255),
        allowNull: false
    },
    llamada: {
        type: Sequelize.STRING(50),
        allowNull: false
    },
    tamano_segmento: {
        type: Sequelize.INTEGER,
        allowNull: false
    },
    fecha_hora_solicitud: {
        type: Sequelize.DATE,
        defaultValue: Sequelize.literal('CURRENT_TIMESTAMP')
    }
}, {
    timestamps: false, // Para desactivar la creación automática de timestamps (createdAt y updatedAt)
    tableName: 'procesos' // Nombre de la tabla en la base de datos
});

module.exports = Proceso;