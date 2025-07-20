package com.example.batterymonitor

import android.util.Log
import com.google.firebase.database.*

class FirebaseManager {

    companion object {
        private const val TAG = "FirebaseManager"
    }

    private val database = FirebaseDatabase.getInstance()
    private val dataRef = database.getReference("esp8266")

    data class BatteryData(
        val BatteryName: String = "",
        val Status: String = "idle",
        val stateOfCharge: Int = 0,
        val stateOfHealth: Int = 0,
        val averageVoltage: Int = 0,
        val averageCurrent: Int = 0,
        val averageTemperature: Int = 0,
        val remainingChargingHours: Int = 0,
        val remainingChargingMinutes: Int = 0,
        val totalChargeCycles: Int = 0,
        val totalChargingTime: Int = 0,
        val faultFlag: Boolean = false,
        val chargeUpFlag: Boolean = false
    )

    interface OnDataReceivedListener {
        fun onDataReceived(data: BatteryData)
        fun onError(error: String)
    }

    fun fetchBatteryData(listener: OnDataReceivedListener) {
        dataRef.addListenerForSingleValueEvent(object : ValueEventListener {
            override fun onDataChange(snapshot: DataSnapshot) {
                try {
                    val data = snapshot.getValue(BatteryData::class.java)
                    if (data != null) {
                        listener.onDataReceived(data)
                    } else {
                        listener.onError("Data is null")
                    }
                } catch (e: Exception) {
                    Log.e(TAG, "Parsing error", e)
                    listener.onError("Error parsing data: ${e.message}")
                }
            }

            override fun onCancelled(error: DatabaseError) {
                Log.e(TAG, "Database error", error.toException())
                listener.onError("Database error: ${error.message}")
            }
        })
    }
}
