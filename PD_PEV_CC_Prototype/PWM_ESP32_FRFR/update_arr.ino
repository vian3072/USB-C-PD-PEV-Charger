void update_measured_arr(){ 
    measured_results[0] = ina228_0x40.getBusVoltage_V();  //Input voltage(V)
    measured_results[1] = ina228_0x40.readCurrent();      //Input current(mA)
    measured_results[2] = ina228_0x40.readPower()/1000;   //Input Power(W)

    measured_results[3] = ina228_0x41.getBusVoltage_V();  //Output Voltage(V)
    measured_results[4] = ina228_0x41.readCurrent();      //Output Current(mA)
    measured_results[5] = ina228_0x41.readPower()/1000;   //Output Power(W)
}
