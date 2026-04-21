import React, { useEffect, useState } from 'react';
import axios from 'axios';
import { AreaChart, Area, XAxis, YAxis, CartesianGrid, Tooltip, ResponsiveContainer } from 'recharts';
// Adicionado Trash2 na lista abaixo
import { Thermometer, Droplets, Wind, RefreshCw, Factory, Settings, LayoutDashboard, Save, Trash2 } from 'lucide-react';

import imagemIndustrial from './images.png';

const App = () => {
  const [data, setData] = useState([]);
  const [view, setView] = useState('dashboard');

  const [brokerConfig, setBrokerConfig] = useState({
    host: '127.0.0.1',
    port: '1883',
    topic: 'sensores/#'
  });

  const fetchData = async () => {
    try {
      const response = await axios.get('http://127.0.0.1:5000/dados');
      setData(response.data.reverse());
    } catch (error) { console.error(error); }
  };

  useEffect(() => {
    fetchData();
    const interval = setInterval(fetchData, 5000);
    return () => clearInterval(interval);
  }, []);

  const handleSaveConfig = async () => {
    try {
      const response = await axios.post('http://127.0.0.1:5000/config', brokerConfig);
      if (response.status === 200) {
        alert("Configurações aplicadas com sucesso!");
        setView('dashboard');
      }
    } catch (error) {
      alert("Falha ao salvar configurações.");
    }
  };

  const handleClearDatabase = async () => {
    if (window.confirm("AVISO: Isso apagará todo o histórico industrial. Confirmar?")) {
      try {
        await axios.delete('http://127.0.0.1:5000/limpar');
        setData([]);
        alert("Banco de dados resetado.");
      } catch (error) {
        console.error("Erro ao limpar:", error);
      }
    }
  };

  return (
    <div style={{
      display: 'flex',
      flexDirection: 'column',
      minHeight: '100vh',
      backgroundColor: '#f0f2f5',
      fontFamily: 'Segoe UI, sans-serif'
    }}>

      {/* HEADER CORPORATIVO */}
      <header style={{ backgroundColor: '#005192', color: 'white', padding: '15px 30px', display: 'flex', justifyContent: 'space-between', alignItems: 'center', boxShadow: '0 2px 4px rgba(0,0,0,0.1)' }}>
        <div style={{ display: 'flex', alignItems: 'center', gap: '15px' }}>
          <Factory size={28} />
          <h1 style={{ margin: 0, fontSize: '20px' }}>FOXCONN | <span style={{ fontWeight: '300' }}>PM Nexus</span></h1>
        </div>

        <nav style={{ display: 'flex', gap: '10px' }}>
          <button onClick={() => setView('dashboard')} style={navButtonStyle(view === 'dashboard')}>
            <LayoutDashboard size={16} /> DASHBOARD
          </button>
          <button onClick={() => setView('settings')} style={navButtonStyle(view === 'settings')}>
            <Settings size={16} /> CONFIGURAÇÕES
          </button>
        </nav>
      </header>

      <main style={{ padding: '30px', flex: 1 }}>
        {view === 'dashboard' ? (
          <>
            {/* TOPO: IMAGEM (ESQUERDA) + BOTÕES (DIREITA) */}
            <div
              style={{
                display: 'flex',
                justifyContent: 'space-between',
                alignItems: 'flex-start',
                marginBottom: '20px',
                gap: '20px',
                flexWrap: 'wrap'
              }}
            >
              {/* IMAGEM */}
              <img
                src={imagemIndustrial}
                alt="Status Industrial"
                style={{
                  width: '250px',
                  maxWidth: '100%',
                  height: 'auto',
                  borderRadius: '8px',
                  boxShadow: '0 4px 6px rgba(0,0,0,0.05)'
                }}
              />

              {/* BOTÕES */}
              <div style={{ display: 'flex', gap: '10px' }}>
                <button onClick={fetchData} style={actionButtonStyle('#005192')}>
                  <RefreshCw size={16} /> ATUALIZAR DADOS
                </button>
                <button onClick={handleClearDatabase} style={actionButtonStyle('#dc2626')}>
                  <Trash2 size={16} /> LIMPAR HISTÓRICO
                </button>
              </div>
            </div>

            {/* DASHBOARDS ABAIXO */}
            <div
              style={{
                display: 'grid',
                gridTemplateColumns: 'repeat(auto-fit, minmax(350px, 1fr))',
                gap: '20px'
              }}
            >
              <ChartCard
                title="Temperatura"
                data={data}
                dataKey="temperatura"
                unit="°C"
                icon={<Thermometer color="#005192" />}
              />
              <ChartCard
                title="Umidade"
                data={data}
                dataKey="humidade"
                unit="%"
                icon={<Droplets color="#005192" />}
              />
              <ChartCard
                title="Partículas"
                data={data}
                dataKey="particulas"
                unit="µg/m³"
                icon={<Wind color="#005192" />}
              />
            </div>
          </>
        ) : (
          /* TELA DE CONFIGURAÇÃO */
          <div
            style={{
              maxWidth: '600px',
              margin: '0 auto',
              backgroundColor: 'white',
              borderRadius: '4px',
              boxShadow: '0 4px 12px rgba(0,0,0,0.1)',
              borderTop: '4px solid #005192'
            }}
          >
            <div style={{ padding: '20px', borderBottom: '1px solid #eee' }}>
              <h2 style={{ margin: 0, color: '#333' }}>Parâmetros do Broker MQTT</h2>
              <p style={{ color: '#666', fontSize: '14px' }}>
                Configure os detalhes de conexão da rede industrial.
              </p>
            </div>

            <div
              style={{
                padding: '30px',
                display: 'flex',
                flexDirection: 'column',
                gap: '20px'
              }}
            >
              <InputGroup
                label="Broker Host (IP)"
                value={brokerConfig.host}
                onChange={(v) => setBrokerConfig({ ...brokerConfig, host: v })}
                placeholder="Ex: 192.168.1.100"
              />
              <InputGroup
                label="Porta"
                value={brokerConfig.port}
                onChange={(v) => setBrokerConfig({ ...brokerConfig, port: v })}
                placeholder="Padrão: 1883"
              />
              <InputGroup
                label="Tópico de Subscrição"
                value={brokerConfig.topic}
                onChange={(v) => setBrokerConfig({ ...brokerConfig, topic: v })}
                placeholder="Ex: fabrica/linha1/#"
              />

              <button
                onClick={handleSaveConfig}
                style={{
                  backgroundColor: '#005192',
                  color: 'white',
                  border: 'none',
                  padding: '12px',
                  borderRadius: '4px',
                  cursor: 'pointer',
                  fontWeight: 'bold',
                  display: 'flex',
                  justifyContent: 'center',
                  alignItems: 'center',
                  gap: '10px',
                  marginTop: '10px'
                }}
              >
                <Save size={18} /> SALVAR CONFIGURAÇÕES
              </button>
            </div>
          </div>
        )}
      </main>

      <footer
        style={{
          marginTop: '30px',
          padding: '15px 30px',
          backgroundColor: '#005192',
          color: 'white',
          textAlign: 'center',
          fontSize: '14px'
        }}
      >
        Desenvolvido por: Denis Moraes Guimarães, Leonardo Souza Gomes, Elthon Batalha Amancio, Igor De Oliveira Damasceno, Carlos Daniel Amazonas Da Silva
      </footer>
    </div>
  );
};

// ... Mantenha as funções de estilo (navButtonStyle, actionButtonStyle, InputGroup) e o componente ChartCard abaixo ...

// Componentes auxiliares de estilização
const navButtonStyle = (isActive) => ({
  backgroundColor: isActive ? 'white' : 'transparent',
  color: isActive ? '#005192' : 'white',
  border: '1px solid white',
  padding: '8px 15px',
  borderRadius: '4px',
  cursor: 'pointer',
  fontWeight: 'bold',
  fontSize: '12px',
  display: 'flex',
  alignItems: 'center',
  gap: '8px',
  transition: '0.2s'
});

const actionButtonStyle = (color) => ({
  backgroundColor: 'white',
  color: color,
  border: `1px solid ${color}`,
  padding: '8px 16px',
  borderRadius: '4px',
  cursor: 'pointer',
  display: 'flex',
  alignItems: 'center',
  gap: '8px',
  fontWeight: 'bold',
  fontSize: '12px',
  boxShadow: '0 2px 4px rgba(0,0,0,0.05)'
});

const InputGroup = ({ label, value, onChange, placeholder }) => (
  <div style={{ display: 'flex', flexDirection: 'column', gap: '8px' }}>
    <label style={{ fontWeight: 'bold', color: '#444', fontSize: '14px' }}>{label}</label>
    <input
      type="text"
      value={value}
      onChange={(e) => onChange(e.target.value)}
      placeholder={placeholder}
      style={{ padding: '10px', border: '1px solid #ccc', borderRadius: '4px', fontSize: '16px' }}
    />
  </div>
);

// Mantenha o ChartCard como estava no passo anterior...

const ChartCard = ({ title, data, dataKey, unit, icon }) => {
  const lastValue = data.length > 0 ? data[data.length - 1][dataKey] : "--";

  return (
    <div style={{ backgroundColor: 'white', borderRadius: '4px', borderTop: '4px solid #005192', boxShadow: '0 4px 12px rgba(0,0,0,0.08)', overflow: 'hidden' }}>
      <div style={{ padding: '20px', borderBottom: '1px solid #eee', display: 'flex', justifyContent: 'space-between', alignItems: 'center' }}>
        <div>
          <span style={{ color: '#666', fontSize: '12px', fontWeight: 'bold' }}>{title.toUpperCase()}</span>
          <h2 style={{ color: '#333', margin: '5px 0 0 0', fontSize: '28px' }}>{lastValue} <span style={{ fontSize: '16px', color: '#999' }}>{unit}</span></h2>
        </div>
        <div style={{ opacity: 0.8 }}>{icon}</div>
      </div>

      <div style={{ width: '100%', height: 250, padding: '10px 0' }}>
        <ResponsiveContainer>
          <AreaChart data={data} margin={{ top: 10, right: 20, left: -10, bottom: 20 }}>
            <defs>
              <linearGradient id="colorFox" x1="0" y1="0" x2="0" y2="1">
                <stop offset="5%" stopColor="#005192" stopOpacity={0.2} />
                <stop offset="95%" stopColor="#005192" stopOpacity={0} />
              </linearGradient>
            </defs>
            <CartesianGrid strokeDasharray="3 3" vertical={false} stroke="#f0f0f0" />

            {/* EIXO X ATUALIZADO */}
            <XAxis
              dataKey="timestamp"
              tickFormatter={(str) => str ? str.split(' ')[1] : ""}
              tick={{ fontSize: 10, fill: '#94a3b8' }}
              minTickGap={50}
              axisLine={{ stroke: '#cbd5e1' }}
            />

            <YAxis tick={{ fontSize: 12, fill: '#94a3b8' }} axisLine={false} />
            <Tooltip
              labelFormatter={(label) => `Horário: ${label}`}
              contentStyle={{ borderRadius: '8px', border: 'none', boxShadow: '0 4px 12px rgba(0,0,0,0.1)' }}
            />

            <Area
              type="monotone" // Usei monotone para ficar mais fluido com o eixo do tempo, mas pode manter o 'stepAfter' se preferir
              dataKey={dataKey}
              stroke="#005192"
              fillOpacity={1}
              fill="url(#colorFox)"
              strokeWidth={2}
              animationDuration={500}
            />
          </AreaChart>
        </ResponsiveContainer>
      </div>
    </div>
  );
};

export default App;