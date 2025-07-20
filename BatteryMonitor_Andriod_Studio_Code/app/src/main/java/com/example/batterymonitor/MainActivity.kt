package com.example.batterymonitor

import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.util.Log
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.google.firebase.FirebaseApp

class MainActivity : AppCompatActivity() {

    private lateinit var batteryNameTextView: TextView
    private lateinit var stateOfChargeTextView: TextView
    private lateinit var stateOfHealthTextView: TextView
    private lateinit var averageVoltageTextView: TextView
    private lateinit var averageCurrentTextView: TextView
    private lateinit var averageTemperatureTextView: TextView
    private lateinit var totalChargeCyclesTextView: TextView
    private lateinit var totalChargingTimeTextView: TextView
    private lateinit var faultFlagTextView: TextView
    private lateinit var chargeUpFlagTextView: TextView
    private lateinit var statusTextView: TextView
    private lateinit var remainingTimeTextView: TextView

    private val handler = Handler(Looper.getMainLooper())
    private lateinit var firebaseManager: FirebaseManager

    private val updateRunnable = object : Runnable {
        override fun run() {
            fetchAndDisplayBatteryData()
            handler.postDelayed(this, 1000) // Repeat every 1 second
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { view, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            view.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        FirebaseApp.initializeApp(this)

        // Initialize all TextViews
        batteryNameTextView = findViewById(R.id.batteryNameTextView)
        stateOfChargeTextView = findViewById(R.id.stateOfChargeTextView)
        stateOfHealthTextView = findViewById(R.id.stateOfHealthTextView)
        averageVoltageTextView = findViewById(R.id.averageVoltageTextView)
        averageCurrentTextView = findViewById(R.id.averageCurrentTextView)
        averageTemperatureTextView = findViewById(R.id.averageTemperatureTextView)
        totalChargeCyclesTextView = findViewById(R.id.totalChargeCyclesTextView)
        totalChargingTimeTextView = findViewById(R.id.totalChargingTimeTextView)
        faultFlagTextView = findViewById(R.id.faultFlagTextView)
        chargeUpFlagTextView = findViewById(R.id.chargeUpFlagTextView)
        statusTextView = findViewById(R.id.statusTextView)
        remainingTimeTextView = findViewById(R.id.remainingTimeTextView)

        firebaseManager = FirebaseManager()
        handler.post(updateRunnable)
    }

    private fun fetchAndDisplayBatteryData() {
        firebaseManager.fetchBatteryData(object : FirebaseManager.OnDataReceivedListener {
            override fun onDataReceived(data: FirebaseManager.BatteryData) {
                batteryNameTextView.text = "Battery Name: ${data.BatteryName}"
                stateOfChargeTextView.text = "State of Charge: ${data.stateOfCharge}%"
                stateOfHealthTextView.text = "State of Health: ${data.stateOfHealth}%"
                averageVoltageTextView.text = "Average Voltage: ${data.averageVoltage} mV"
                averageCurrentTextView.text = "Average Current: ${data.averageCurrent} mA"
                averageTemperatureTextView.text = "Average Temperature: ${data.averageTemperature} °C"
                totalChargeCyclesTextView.text = "Total Charge Cycles: ${data.totalChargeCycles}"
                totalChargingTimeTextView.text = "Total Charging Time: ${data.totalChargingTime} min"
                faultFlagTextView.text = "Fault Flag: ${data.faultFlag}"
                chargeUpFlagTextView.text = "Charge Up Flag: ${data.chargeUpFlag}"
                statusTextView.text = "Status: ${data.Status}"
                remainingTimeTextView.text = "Remaining Time: ${data.remainingChargingHours} h ${data.remainingChargingMinutes} m"
            }

            override fun onError(error: String) {
                Log.e("MainActivity", "Firebase error: $error")
            }
        })
    }

    override fun onDestroy() {
        super.onDestroy()
        handler.removeCallbacks(updateRunnable)
    }
}
