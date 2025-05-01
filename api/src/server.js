const express = require("express");
const cors = require("cors");
const db = require("./firebaseservice");

const app = express();
app.use(cors());

const PORT = 3001;

app.get("/api/graficos", async (req, res) => {
  try {
    const ref = db.ref("Graficos/DataHora");
    const snapshot = await ref.once("value");
    const data = snapshot.val();

    if (!data) return res.status(404).json({ message: "Nenhum dado encontrado" });

    res.json(data);
  } catch (err) {
    console.error("Erro ao buscar dados:", err);
    res.status(500).json({ error: "Erro ao buscar dados" });
  }
});

app.listen(PORT, () => {
  console.log(`Servidor rodando em http://localhost:${PORT}`);
});
