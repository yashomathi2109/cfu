*** Settings ***
Suite Setup                   Setup
Suite Teardown                Teardown
Test Setup                    Reset Emulation
Test Teardown                 Test Teardown
Resource                      ${RENODEKEYWORDS}

*** Keywords ***
Create Machine
    Execute Command          include @${CURDIR}/digilent_arty.resc
    Create Terminal Tester   sysbus.uart

    Start Emulation

*** Test Cases ***
Should Run shufflenet with zeros input
    Create Machine

    Wait For Line On Uart    CFU Playground
    Wait For Prompt On Uart  main>
    Write Line To Uart       1
    Wait For Prompt On Uart  models>
    Write Line To Uart       1
    Wait For Prompt On Uart  shufflenet>
    Write Line To Uart       z
    Wait For Line On Uart    Result is 20
    Wait For Prompt On Uart  shufflenet>

