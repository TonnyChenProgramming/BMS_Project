package com.example.batterymonitor

import org.json.JSONObject

data class BmsData(
    val batteryName: String,
    val stateOfCharge: Int,
    val stateOfHealth: Int,
    val averageVoltage: Float,
    val averageCurrent: Float,
    val averageTemperature: Float,
    val totalChargeCycles: Int,
    val totalChargingTime: Int,
    val faultFlag: Boolean,
    val chargeUpFlag: Boolean
) {
    companion object {
        fun fromJson(json: JSONObject): BmsData {
            return BmsData(
                batteryName = json.getString("batteryName"),
                stateOfCharge = json.getInt("stateOfCharge"),
                stateOfHealth = json.getInt("stateOfHealth"),
                averageVoltage = json.getDouble("averageVoltage").toFloat(),
                averageCurrent = json.getDouble("averageCurrent").toFloat(),
                averageTemperature = json.getDouble("averageTemperature").toFloat(),
                totalChargeCycles = json.getInt("totalChargeCycles"),
                totalChargingTime = json.getInt("totalChargingTime"),
                faultFlag = json.getBoolean("faultFlag"),
                chargeUpFlag = json.getBoolean("chargeUpFlag")
            )
        }
    }
}
