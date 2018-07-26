import os

def GetFileList(dir, fileList):
    newDir = dir
    if os.path.isfile(dir):
        #fileList.append(dir.decode('gbk'))
        fileList.append(dir)
    elif os.path.isdir(dir):
        for s in os.listdir(dir):
            #ignore file/direcotry
            #if s == "xxx":
            #continue
            newDir=os.path.join(dir,s)
            GetFileList(newDir, fileList)
    return fileList

AUTOTEST_WORKSPACE = 'D:\\autotest_workspace'
CLOUD_PLATFORM_DIR = 'D:\\autotest_workspace\\private-cloud'
AUTO_TEST_DIR = 'D:\\autotest_workspace\\test\\WebAutoTest'
COMPILE_DIR = 'D:\\autotest_workspace\\test\\WebAutoTest'
TOMCAT_DIR = 'D:\\Tomcat'
BUILD_DIR = 'D:\\autotest_workspace\\test\\compilerC'
CLOUD_PLATFORM_TESTCASE_DIR = 'D:\\autotest_workspace\\test\\testcase\\cloudPlatform'
AUTHORIZATION_TESTCASE_DIR = "D:\\autotest_workspace\\test\\testcase\\Palace\\authorization"
USER_TESTCASE_DIR = "d:\\autotest_workspace\\test\\testcase\\Palace\\User"
PERSONALCLOUD_TESTCASE_DIR = "d:\\autotest_workspace\\test\\testcase\\Palace\\PersonalCloud"
CLOUD_PLATFORM_GIT_URL = 'git@192.168.100.228:gugong/private-cloud.git'
AUTO_TEST_GIT_URL = 'git@192.168.100.228:gugong/test.git'

'''workspace'''
if not os.path.exists(AUTOTEST_WORKSPACE):
    os.mkdir(AUTOTEST_WORKSPACE)
os.chdir(AUTOTEST_WORKSPACE)

'''deploy platform
if os.path.exists("private-cloud"):
    os.system("rm -rf private-cloud")
print('begin download cloud platform source code')
os.system('git clone ' + CLOUD_PLATFORM_GIT_URL)
if os.path.exists("private-cloud"):
    print('download cloud platform source code success')
else:
    print('download cloud platform source code fail')
    exit(1)
os.chdir(CLOUD_PLATFORM_DIR)
print('begin to package cloud platform')
os.system("mvn package")
target_files = os.listdir('target')
war_files = []
for _file in target_files:
    if _file.endswith('.war'):
        war_files.append(_file)
if len(war_files) > 1:
    print('Too many war files')
    exit(1)
print('package cloud platform success')
os.system('cp target\\' + war_files[0] + ' ' + TOMCAT_DIR + '\\webapps')
print('begin to deploy cloud platform')
os.chdir(TOMCAT_DIR)
os.system('bin\\shutdown.bat')
os.system('bin\\startup.bat')
'''


'''deploy autotest
os.chdir(AUTOTEST_WORKSPACE)
if os.path.exists("test"):
    os.system("rm -rf test")
os.system('git clone ' + AUTO_TEST_GIT_URL)
if os.path.exists("test"):
    print('download auto test source code success')
else:
    print('download auto test source code fail')
    exit(1)
'''

'''build cloudplatform testcase
os.chdir(BUILD_DIR)
fileList = GetFileList(CLOUD_PLATFORM_TESTCASE_DIR, [])
size = 0
for e in fileList:
    if e.endswith('.t'):
        size = size + 1
        status = os.system('win_test_generator.exe ' + e + ' cloudplatform')
        if status != 0:
            print('---' + e + ' file compiled faile---')
print ('-----totally build ' + str(size) + ' cloudplatform testcases------')
'''

'''build authorization testcase'''
os.chdir(BUILD_DIR)
fileList = GetFileList(AUTHORIZATION_TESTCASE_DIR, [])
size = 0
for e in fileList:
    if e.endswith('.t'):
        size = size + 1
        status = os.system('win_test_generator.exe ' + e + ' authorization')
        if status != 0:
            print('---' + e + ' file compiled faile---')
print ('-----totally build ' + str(size) + ' authorization testcases------')



'''build user testcase
os.chdir(BUILD_DIR)
fileList = GetFileList(USER_TESTCASE_DIR, [])
size = 0
for e in fileList:
    if e.endswith('.t'):
        size = size + 1
        status = os.system('win_test_generator.exe ' + e + ' user')
        if status != 0:
            print('---' + e + ' file compiled faile---')
print ('-----totally build ' + str(size) + ' user testcases------')
'''

'''build personal cloud testcase
os.chdir(BUILD_DIR)
fileList = GetFileList(PERSONALCLOUD_TESTCASE_DIR, [])
size = 0
for e in fileList:
    if e.endswith('.t'):
        size = size + 1
        status = os.system('win_test_generator.exe ' + e + ' personalCloud')
        if status != 0:
            print('---' + e + ' file compiled faile---')
print ('-----totally build ' + str(size) + ' user testcases------')
'''

#begin to test
os.chdir(AUTO_TEST_DIR)
if os.path.exists('target'):
    os.system('rm -rf target')
#os.system('mvn surefire-report:report')
print('Done')





