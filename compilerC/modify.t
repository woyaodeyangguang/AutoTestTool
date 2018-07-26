int null;
void Modify_zone_info(zone_for_edit, zone_name, num_cpu, memory_size, disk_size, description)
{
  expectToSeeLinkText("域组管理");
  clickLink("域组管理");
  expectToSeeLinkText(zone_for_edit);
  clickLink(zone_for_edit, "link_text");
  expectToSee("id", "openModifyDomainDialogButton");
  click("id", "openModifyDomainDialogButton");
	 
  feedTextBox("id", "domainNameText", zone_name);
	feedTextBox("id", "domainCpuText", num_cpu);
	feedTextBox("id", "domainMemoryText", memory_size);
	feedTextBox("id", "domainHarddiskText", disk_size);
	feedTextBox("id", "domainDescriptionText", description);

	click("id", "modifyDomainButton");

	/*	%% 检查修改是否生效
	% t: table, f: field
	% "基本信息"下面的第一个table
	*/
	//t = Find_table_in_zone("基本信息", 0);
	//now_zone_name = zone_for_edit;
	if(zone_name != null)
	{
	  //"名称” 为zone_name的一行，其中的“处理器”一列
	  //		f = Find_field_in_table(t, "名称", zone_name, "处理器");
	  //	now_zone_name = zone_name;
	  //TODO: Define it: expectToSeeFieldinTable(key_of_row, row, col, elemenType, key);
	  expectToSeeFieldInTable("名称", zone_name, "处理器", "text", num_cpu);
	}
	else {
	  expectToSeeValue("text", zone_name);
	}
	/*
	if(num_cpu != Null)
	{
		f = Find_field_in_table(t, "名称", zone_name, "处理器");
		Expect_to_see_value(f, "text", num_cpu);
	}
	if(memory_size != Null)
	{
		f = Find_field_in_table(t, "名称", zone_name, "内存");
		Expect_to_see_value(f, "text", memory_size);
	}
	if(disk_size != Null)
	{
		f = Find_field_in_table(t, "名称", zone_name, "硬盘");
		Expect_to_see_value(f, "text", disk_size);
	}
	if(description != Null)
	{
		f = Find_field_in_table(t, "名称", zone_name, "描述");
		Expect_to_see_value(f, "text", description);
	}

  click("id", "openModifyDomainDialogButton");
  if(zone_name != 0)
    {
      //"名称” 为zone_name的一行，其中的“处理器”一列
      //f = Find_field_in_table(t, "名称", zone_name, "处理器");
      click("id", description);
      Expect_to_see_value( "text", num_cpu);
    }
	*/
}

void modifyZoneInfoError(zoneForEdit, zoneName, numCPU, memorySize, diskSize, description, expectErrInfo) {
  char* zoneForEdit = null;
  char* num_cpu = "8";
  expectToSeeLinkText("编辑", num_cpu);
}

void error1(zoneForEdit, zoneName, numCPU, memorySize, diskSize, description, expectErrInfo) {
  modifyZoneInfoError(zoneForEdit, zoneName, numCPU, memorySize, diskSize, description, expectErrInfo) ;
}

void test() {
  //TODO: may support multiple test sequences
  char* a;
  error1("zone1", "zone3", null, null, null, null, null);
  error1("zone2", "zone3", null, null, null, null, null);
}
