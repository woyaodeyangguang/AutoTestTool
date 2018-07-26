/*%%调整告警设置
%%假设初始值都是开启
*/

//function login(url, user_name, user_id, user_passwd); //predefined macro

function set_settings(checkbox_id, checkbox, text_id, text, select_id, select) {
  //Find the switchlabel by checkbox_id, and go to the next 1 "<>"
  //b = Find_switchlabel_by_position("id", checkbox_id, 1);
  //  Click_switchlabel(b);
  click("id", checkbox_id);
  if( checkbox == "True") {
    //Click_switchlabel(b);
    click("id", checkbox_id);
    feedTextBox("id", text_id, text);
    selectDropDownBox("id", select_id, select);
  }
}

function check_settings(checkbox_id, checkbox, text_id, text, select_id, select) {
  //Find the switchlabel by checkbox_id, and go to the next 1 "<>"
  //  b = Find_switchlabel_by_position("id", checkbox_id, 1);
  if( checkbox == "False") {
    //The two components are disabled
    expectToSeeValue("id", text_id, "disabled", "disabled");
    Expect_to_see_value("id", select_id, "disabled", "disabled");  
    Click_switchlabel(b);
  }
  else {
    //The two components have the right values
    Expect_to_see_value("id", text_id, "value", text);
    Expect_to_see_value("id", select_id, "selected", select);
  }
}


function Checkbox_virtualmachine_alarm_setting(virtualMachine, cpuUtilCheckbox, cpuUtilThreshold, cpuUtilServeritySelect, memoryUsageCheckbox, memoryUsageThreshold, memoryUsageSeveritySelect, diskReadCheckbox, diskReadThreshold, diskReadSeveritySelect, diskWriteCheckbox, diskWriteThreshold, diskWriteSeveritySelect, networkOutgoingCheckbox, networkOutgoingThreshold, networkOutgoingSeveritySelect, networkIncomingCheckbox, networkIncomingThreshold, networkOutgoingSeveritySelect)
{
  login(url, "王云", "wangyun", "12345");
  Click_link("虚拟机");
  Click_link(virtualMachine);
  Click_link("openSetAlarmSettingsDialogButton");
  
  set_settings("cpuUtilCheckbox", cpuUtilCheckbox, "cpuUtilThreshold", cpuUtilThreshold, "cpuUtilSeveritySelect", cpuUtilSeveritySelect);

  set_settings("memoryUsageCheckbox", memoryUsageCheckbox, "memoryUsageThreshold", memoryUsageThreshold, "memoryUsageSeveritySelect", memoryUsageSeveritySelect);

  set_settings("diskReadCheckbox", diskReadCheckbox, "diskReadThreshold", diskReadThreshold, "diskReadSeveritySelect", diskReadSeveritySelect);

  set_settings("diskWriteCheckbox", diskWriteCheckbox, "diskWriteThreshold", diskWriteThreshold, "diskWriteSeveritySelect", diskWriteSeveritySelect);

  set_settings("networkOutgoingCheckbox", networkOutgoingCheckbox, "networkOutgoingThreshold", networkOutgoingThreshold, "networkOutgoingSeveritySelect", networkOutgoingSeveritySelect);

  set_settings("networkIncomingCheckbox", networkIncomingCheckbox, "networkIncomingThreshold", networkIncomingThreshold, "networkIncomingSeveritySelect", networkIncomingSeveritySelect);

    
  Click("id", "setAlarmSettingsButton");
  Expected_to_see("id", "openSetAlarmSettingsDialogButton");
  /*
  t = find_by_id("mahcineAlarmSettingTable");
  d = find_in_table(t, "id", "处理器利用率", "id", "监控名称");
  if(testCpuUtil) { 
    Expected_to_see_element(d, cpuUtilThreshold);
  }
  */

  Click_link("openSetAlarmSettingsDialogButton");

  check_settings("cpuUtilCheckbox", cpuUtilCheckbox, "cpuUtilThresholdText", cpuUtilThresholdText, "cpuUtilSeveritySelect", cpuUtilSeveritySelect);
  
  check_settings("memoryUsageCheckbox", memoryUsageCheckbox, "memoryUsageThresholdText", memoryUsageThresholdText, "memoryUsageSeveritySelect", memoryUsageSeveritySelect);

  check_settings("diskReadCheckbox", diskReadCheckbox, "diskReadThresholdText", diskReadThresholdText, "diskReadSeveritySelect", diskReadSeveritySelect);
  
  check_settings("diskWriteCheckbox", diskWriteCheckbox, "diskWriteThresholdText", diskWriteThresholdText, "diskWriteSeveritySelect", diskWriteSeveritySelect);
  
  check_settings("networkOutgoingCheckbox", networkOutgoingCheckbox, "networkOutgoingThresholdText", networkOutgoingThresholdText, "networkOutgoingSeveritySelect", networkOutgoingSeveritySelect);
  
  check_settings("networkIncomingCheckbox", networkIncomingCheckbox, "networkIncomingThresholdText", networkIncomingThresholdText, "networkIncomingSeveritySelect", networkIncomingSeveritySelect);  
}

%%tests

test_virtualmachine_alarm_setting("demo01", true, 80, "NORMAL", true, 80, "NORMAL", true, 10000, "NORMAL",  true, 10000, "NORMAL",  true, 10000, "NORMAL",  true, 10000, "NORMAL");

test_virtualmachine_alarm_setting("demo01", false, 80, "NORMAL", false, 70, "NORMAL", false, 10000, "NORMAL",  false, 10000, "NORMAL",  false, 10000, "NORMAL",  false, 10000, "NORMAL");

test_virtualmachine_alarm_setting("demo01", true, 70, "BELOW_NORMAL", true, 70, "BELOW_NORMAL", true, 1000, "BELOW_NORMAL",  true, 1000, "BELOW_NORMAL",  true, 1000, "BELOW_NORMAL",  true, 1000, "BELOW_NORMAL");

test_virtualmachine_alarm_setting("demo01", true, 80, "LOWEST", true, 80, "LOWEST", true, 10000, "LOWEST",  true, 10000, "LOWEST",  true, 10000, "LOWEST",  true, 10000, "LOWEST");

test_virtualmachine_alarm_setting("demo01", true, 80, "ABOVE_NORMAL", true, 80, "ABOVE_NORMAL", true, 10000, "ABOVE_NORMAL",  true, 10000, "ABOVE_NORMAL",  true, 10000, "ABOVE_NORMAL",  true, 10000, "ABOVE_NORMAL");

test_virtualmachine_alarm_setting("demo01", true, 80, "HIGHEST", true, 80, "HIGHEST", true, 10000, "HIGHEST",  true, 10000, "HIGHEST",  true, 10000, "HIGHEST",  true, 10000, "HIGHEST");

test_virtualmachine_alarm_setting("demo01", true, -1, "NORMAL", true, 80, "NORMAL", true, 10000, "NORMAL",  true, 10000, "NORMAL",  true, 10000, "NORMAL",  true, 10000, "NORMAL");

test_virtualmachine_alarm_setting("demo01", true, 80, "NORMAL", true, -1, "NORMAL", true, 10000, "NORMAL",  true, 10000, "NORMAL",  true, 10000, "NORMAL",  true, 10000, "NORMAL");

test_virtualmachine_alarm_setting("demo01", true, 80, "NORMAL", true, 80, "NORMAL", true, -1, "NORMAL",  true, 10000, "NORMAL",  true, 10000, "NORMAL",  true, 10000, "NORMAL");

test_virtualmachine_alarm_setting("demo01", true, 80, "NORMAL", true, 80, "NORMAL", true, 10000, "NORMAL",  true, -1, "NORMAL",  true, 10000, "NORMAL",  true, 10000, "NORMAL");

test_virtualmachine_alarm_setting("demo01", true, 80, "NORMAL", true, 80, "NORMAL", true, 10000, "NORMAL",  true, 10000, "NORMAL",  true, -1, "NORMAL",  true, 10000, "NORMAL");

test_virtualmachine_alarm_setting("demo01", true, 80, "NORMAL", true, 80, "NORMAL", true, 10000, "NORMAL",  true, 10000, "NORMAL",  true, 10000, "NORMAL",  true, -1, "NORMAL");

test_virtualmachine_alarm_setting("demo01", true, 120, "NORMAL", true, 80, "NORMAL", true, 10000, "NORMAL",  true, 10000, "NORMAL",  true, 10000, "NORMAL",  true, 10000, "NORMAL");

test_virtualmachine_alarm_setting("demo01", true, 80, "NORMAL", true, 120, "NORMAL", true, 10000, "NORMAL",  true, 10000, "NORMAL",  true, 10000, "NORMAL",  true, 10000, "NORMAL");

