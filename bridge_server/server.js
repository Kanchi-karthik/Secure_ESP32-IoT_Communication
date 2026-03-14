const express = require("express");
const fetch = (...args) =>
  import("node-fetch").then(({ default: fetch }) => fetch(...args));

const app = express();

/* ESP32 sends plain text body */
app.use(express.text());

/* Firebase database URL */
const firebaseURL =
"const firebaseURL = "YOUR_FIREBASE_DATABASE_URL";";

/* Base64 decode */
function decryptMessage(msg)
{
  return Buffer.from(msg, "base64").toString();
}

app.post("/", async (req, res) => {

  try {

    /* device authentication */
    if (req.headers["device-key"] !== "ESP32_SECRET_123") {
      console.log("Unauthorized device attempted connection\n");
      return res.status(403).send("Unauthorized");
    }

    const encrypted = req.body;

    console.log("\n========== ESP32 MESSAGE RECEIVED ==========");

    console.log("\nEncrypted data:");
    console.log(encrypted);

    const decrypted = decryptMessage(encrypted);

    console.log("\nDecrypted message:");
    console.log(decrypted);

    await fetch(firebaseURL, {
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify({
        message: decrypted,
        timestamp: Date.now()
      })
    });

    console.log("\nStored in Firebase successfully");

    res.send("stored");

  } catch (error) {

    console.error("Bridge error:", error);
    res.status(500).send("server error");

  }

});

/* start bridge server */
app.listen(3000, "0.0.0.0", () => {

  console.log("====================================");
  console.log("ESP32 Secure Bridge Server Running");
  console.log("Listening on port 3000");
  console.log("====================================\n");

});