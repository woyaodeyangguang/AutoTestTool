package com.sinosoft.selenium;
import org.junit.Test;
public class modify {
BaseCommon base = new BaseCommon();
public void Modify_zone_info(String zone_for_edit, String zone_name, String num_cpu, String memory_size, String disk_size, String description) {
base.expectToSeeLinkText("域组管理");
base.clickLink("域组管理");
base.expectToSeeLinkText(zone_for_edit);
base.clickLink(zone_for_edit, "link_text");
base.expectToSee("id", "openModifyDomainDialogButton");
base.click("id", "openModifyDomainDialogButton");
base.feedTextBox("id", "domainNameText", zone_name);
base.feedTextBox("id", "domainCpuText", num_cpu);
base.feedTextBox("id", "domainMemoryText", memory_size);
base.feedTextBox("id", "domainHarddiskText", disk_size);
base.feedTextBox("id", "domainDescriptionText", description);
base.click("id", "modifyDomainButton");
if(zone_name==null) {
base.expectToSeeFieldInTable("名称", zone_name, "处理器", "text", num_cpu);
}
 else {
base.expectToSeeValue("text", zone_name);
}
}
public void modifyZoneInfoError(String zoneForEdit, String zoneName, String numCPU, String memorySize, String diskSize, String description, String expectErrInfo) {
String zoneForEdit=null;
String num_cpu="8";
base.expectToSeeLinkText("编辑", num_cpu);
}
public void error1(String zoneForEdit, String zoneName, String numCPU, String memorySize, String diskSize, String description, String expectErrInfo) {
modifyZoneInfoError(zoneForEdit, zoneName, numCPU, memorySize, diskSize, description, expectErrInfo);
}
private String a;
@Test
public void Test1() {
error1("zone1", "zone3", null, null, null, null, null);
}
@Test
public void Test2() {
error1("zone2", "zone3", null, null, null, null, null);
}
}
