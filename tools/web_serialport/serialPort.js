let port = null;
let reading = false;   // 关闭读操作
let isClosing = false; // 检查关闭操作是否已经在进行中
let reader;
let targetBox;
let buttonName = null;
let lastButtonName = null;
let targetId = null;
let buttonFlag = false;
let lastGroup;
let programFlag = false;
let lastProgram_flag = false;
let programLast_dataLength;
const data1 = new Uint8Array([0x55]);
const data2 = new Uint8Array([0x3C,0x3C,0xA5,0xA5]);
// LEO :使能dpll，写0x4000a034 = 0297； 切主频为144M，写0x4000a02c = 01011580
const LEO_144M = "2,4000a034,0297,4000a02c,01011580";
// LM3050 :使能dpll，写0x4000d034 = 039b； 切主频为28M，写0x4000d02c = 01000580
const LM3050_128M = "2,4000d034,039b,4000d02c,01000580";


async function openSerialPort(baudRate_temp) {
  let baudRate_fuzhi;
  const baudRate = parseInt(document.getElementById("baudRate").value);

  if (isNaN(baudRate)) {
    console.error("无效的波特率");
    return;
  }
  if(parseInt(baudRate_temp))
  {
    baudRate_fuzhi = baudRate_temp;

  }else{
    baudRate_fuzhi = baudRate;
  }
  try {
    port = await navigator.serial.requestPort();
    await port.open({
      baudRate: baudRate_fuzhi,
      dataBits: 8,
      stopBits: 1,
      parity: "none"
    });
    console.log("已打开串口，波特率:", baudRate);
    const portStatusDiv = document.getElementById("portStatus");
    portStatusDiv.textContent = "串口已打开";
    portStatusDiv.style.color = "green"; 
    reading = true;
    readData();
  } catch (error) {
    console.error("打开串口时发生错误:", error);
  }
}

// 关闭串口
async function closeSerialPort() {
  if (port && !isClosing) {
    isClosing = true;
    reading = false;
    if (reader) {
      try {
        await reader.cancel();
        reader = null;
      } catch (error) {
        console.error('Failed to cancel reader:', error);
      }
    }
    try {
      setTimeout(async () => {
        try {
          if (port && !port.closed) {
            await port.close();
            port = null;
            const portStatusDiv = document.getElementById("portStatus");
            portStatusDiv.textContent = "串口已关闭";
            portStatusDiv.style.color = "red";
          }
        } catch (error) {
          console.error('Failed to close serial port:', error);
        }
        isClosing = false; 
      }, 100);
    } catch (error) {
      console.error('Failed to close serial port:', error);
    }
  }
}

async function readData() {
  let lastLineLength;
  let lastLineData;
  let init_flag = false;
  let receiveData;
  if (port && !port.readable.locked) {
    while (reading) {
      try {
        reader = port.readable.getReader();
        while (reading) {
          const { value, done } = await reader.read();
          if (done) {
            console.log("接收完成");
            break;
          }
          const hexData = Array.prototype.map.call(value, x => {
            const hex = x.toString(16);
            return hex.length === 1 ? '0' + hex : hex;
          }).join(' ');
          if(buttonName != lastButtonName || buttonName === null)
          {
            lastButtonName = buttonName;
            document.getElementById("receiverText").textContent += `\n收<—：${hexData}`;
          }else{
            document.getElementById("receiverText").textContent += ` ${hexData}`;
          }

          if(buttonName != null){
            const lines = document.getElementById("receiverText").textContent.split("\n");
            const lastLine = lines[lines.length - 1].trim();          
            if (lastLine.startsWith("收<—")) {
              lastLineData = lastLine.substring(4); 
              lastLineLength = Math.floor(lastLineData.replace(/ /g, '').length / 2);
            }
            // 处理最终接收到的数据
            if(lastLineLength > 2){
              lastLineData = lastLineData.substring(6).split(" ").reverse().join(" ");
              if(programFlag == true){
              // 烧录满256字节时的数据处理
                if(lastLineData.length == 256*2 + 255){
                  receiveData =  lastLineData.replace(/\s/g, '');
                  console.log("receiveData",receiveData)
                  console.log("lastGroup",lastGroup)
                  if(receiveData === lastGroup)
                  {
                    console.log("下载成功");
                  }else{
                    alert("Flash Program Failure");
                  }
                }else if((lastLineData.length == programLast_dataLength*2 + (programLast_dataLength-1)) && (programLast_dataLength != 0) && (lastProgram_flag == true)){
                  receiveData =  lastLineData.replace(/\s/g, '');
                  console.log("receiveData--",receiveData)
                  console.log("lastGroup--",lastGroup)
                  if(receiveData === lastGroup)
                  {
                    alert("Flash Program Successed");
                    programFlag = false;
                  }else{
                    alert("Flash Program Failure");
                  }
                }
              }
              if(buttonFlag == true){
                targetBox.textContent = lastLineData;
              }
            } else {
              if (lastLineData.substring(0, 2) === buttonName.toString(16).slice(2)) {
                if (buttonFlag == true) {
                  if (lastLineData.substring(3) == '00') {
                    targetBox.textContent = ` NO_ERROR`;
                  }
                  else if (lastLineData.substring(3) == '01') {
                    targetBox.textContent = ` ERROR`;
                  }
                  else if (lastLineData.substring(3) == '02') {
                    targetBox.textContent = ` FEATURE_DISABLED`;
                  }
                }
              } else if (lastLineData.substring(0, 2) === 'ff') {
                targetBox.textContent = ` 无效命令`;
              }
            }
          }
          // 在接收到0xaa之后发送同步字
          if (hexData === 'aa' && (init_flag == false)) {
            init_flag = true;
            lastButtonName = null;
            targetBox = null;
            InitData_template(data2);
          }
        }
      } catch (error) {
        console.error("Error reading data:", error);
      } finally {
        if (reader) {
          reader.releaseLock();
        }
      }
    }
  }
}

function InitData(){
  lastButtonName = null;
  targetBox = null;
  InitData_template(data1);
}

async function InitData_template(data) {
  lastButtonName = null;
  buttonName = "初始同步命令";
  try {
    const writer = port.writable.getWriter();
    await writer.write(data);
    const hexData = Array.prototype.map.call(data, x => x.toString(16)).join(' ');
    document.getElementById("receiverText").textContent += `\n发—>：${hexData}`;
    writer.releaseLock();
  } catch (error) {
    console.error('写入数据到串口设备时发生错误:', error);
  }
}

async function sendData(button) {
  lastButtonName = null;
  buttonFlag = false;
  if (button.type === 'button') {
    buttonFlag = true;
    buttonName = button.innerText;    
    targetId = button.getAttribute("data-target");
    targetBox = document.getElementById(targetId);
    targetBox.textContent = null;
  }else{
    buttonName = button;
  }
  const data = new Uint8Array([buttonName]);
    try {
      const writer = port.writable.getWriter();
      await writer.write(data);
      writer.releaseLock();
      const hexData = Array.prototype.map.call(data, x => {
        const hex = x.toString(16);
        return hex.length === 1 ? '0' + hex : hex;
      }).join(' ')
      document.getElementById("receiverText").textContent += `\n发—>：${hexData}`;
    } catch (error) {
      console.error('写入数据到串口设备时发生错误:', error);
    }
}

async function SendMultipleData(button, inputId) {
  let inputValue;
  const bytes = [];
  lastButtonName = null;
  buttonFlag = false;
  if (button.type === 'button') {
    buttonFlag = true;
    buttonName = button.innerText;
    inputValue = document.getElementById(inputId).value;
    const targetId = button.getAttribute("data-target");
    targetBox = document.getElementById(targetId);
    targetBox.textContent = null;
  } else {
    buttonName = button;
    inputValue = inputId;
  }
  const result = convertToLittleEndianHexArray(inputValue, buttonName);
  // console.log("result: " + result);
  bytes.push(buttonName);
  for (let i = 0; i < result.length; i++) {
    const byte = parseInt(result.slice(i, i + 1), 16);
    bytes.push(byte);
  }
  try {
    const writer = port.writable.getWriter();
    const data = new Uint8Array(bytes);
    await writer.write(data);
    writer.releaseLock();
    const hexData = Array.prototype.map.call(data, x => {
      const hex = x.toString(16);
      return hex.length === 1 ? '0' + hex : hex;
    }).join(' ');

    document.getElementById("receiverText").textContent += `\n发—>：${hexData}`;
  } catch (error) {
    console.error('写入数据到串口设备时发生错误:', error);
    alert(error.message);
  }
}

function convertToLittleEndianHexArray(input, buttonName) {
  const groups = input.split(',');
  const groupCount = groups.length;
  const fistData = groups[0];
  if (groupCount == 3) {
    lastGroup = groups[2];
  }
  if ((buttonName == '0x16') && (groups.length < (parseInt(fistData, 16) * 2) + 1)) {
    alert("输入格式错误");
  }
  console.log("分组数", groupCount)
  const result = [];
  groups.forEach((group, index) => {
    const bytes = group.split('');
    if (buttonName == '0x00' || buttonName == '0x01' || buttonName == '0x03' || buttonName == '0x04' || buttonName == '0x0b' || buttonName == '0x0c' || buttonName == '0x0d' || buttonName == '0x17' || buttonName == '0x1b') {
      while (bytes.length < 8) {
        bytes.unshift(0);
      }
    } else if (buttonName == '0x02' || buttonName == '0x09' || buttonName == '0x0a' || buttonName == '0x18') {
      if (index < groupCount - 1) {
        while (bytes.length < 8) {
          bytes.unshift(0);
        }
      } else if (bytes.length < 2) {
        bytes.unshift(0);
      }
    } else if (buttonName == '0x08') {
      while (bytes.length < 4) {
        bytes.unshift(0);
      }
    } else if (buttonName == '0x12' || buttonName == '0x05' || buttonName == '0x19') {
      while (bytes.length < 2) {
        bytes.unshift(0);
      }
    } else if (buttonName == '0x13' || buttonName == '0x14') {
      if (index == 0) {
        while (bytes.length < 6) {
          bytes.unshift(0);
        }
      } else if (index == 1 || index == 3) {
        while (bytes.length < 2) {
          bytes.unshift(0);
        }
      } else if (index == 2) {
        while (bytes.length < 8) {
          bytes.unshift(0);
        }
      }
    } else if (buttonName == '0x16') {
      if (index == 0) {
        while (bytes.length < 2) {
          bytes.unshift(0);
        }
        console.log("--", fistData);
      }
      if (index < groups.length && index > 0) {
        while (bytes.length < 8) {
          bytes.unshift(0);
        }
      }
    }
    for (let i = bytes.length - 2; i >= 0; i -= 2) {
      const byte = parseInt(bytes[i] + bytes[i + 1], 16);
      result.push(byte);
    }
  });
  const hexResult = result.map(byte => {
    const hex = byte.toString(16);
    return hex.length === 1 ? '0' + hex : hex;
  });
  return hexResult;
}

// 切为最高主频
async function highest_MainFrequency() {
  var buttonId = event.target.id;
  let inputValue;
  const baudRate = parseInt(document.getElementById("baudRate").value);
  var optionExists = false;
  var select = document.getElementById("baudRate");
  let newBaudRate;
  if (buttonId === "LEO") {
    // 24M->144M （6倍）
    inputValue = LEO_144M;
    newBaudRate = baudRate * 6;
  } else if (buttonId === "LM3050") {
    // 24M->128M （5倍）
    inputValue = LM3050_128M;
    newBaudRate = baudRate * 5;
  }
  await  new Promise((resolve, reject) => {     
    setTimeout(async()=> {
     try{
       SendMultipleData("0x16", inputValue);
       resolve();
       alert("主频切换成功，请选择串口");
       for (var i = 0; i < select.options.length; i++) {
         if (select.options[i].value == newBaudRate) {
           optionExists = true;
         }
       }
       if (!optionExists) {
         var newOptionText = newBaudRate.toString();
         var newOption = new Option(newOptionText, newBaudRate);
         select.add(newOption);
         select.value = newBaudRate;
       } else {
         document.getElementById("baudRate").value = newBaudRate;
       }
     }catch(error){
       reject(error);
     }
   }, 300);
 });
  closeSerialPort();
  openSerialPort(newBaudRate);
}

// flash烧录
async function download_bin() {
  programFlag = true;
  const fileInput = document.getElementById("fileInput");
  const fileNameDisplay = document.getElementById("fileName");
  await new Promise((resolve, reject) => {
    setTimeout(async () => {
      try {
        await flash_init("0x19", 01);
        resolve();
      } catch (error) {
        reject(error);
      }
    }, 100);
  });
  await new Promise((resolve, reject) => {
    setTimeout(async () => {
      try {
        await flash_chip_erase("0x05", 60);
        resolve();
      } catch (error) {
        reject(error);
      }
    }, 100);
  });
  fileInput.addEventListener("change", function () {
    const selectedFile = fileInput.files[0];
    if (selectedFile) {
      const fileSize = selectedFile.size;
      const reader = new FileReader();
      reader.onload = function (event) {
        const arrayBuffer = event.target.result;
        fileNameDisplay.textContent = `已选择文件: ${selectedFile.name}`;
        console.log("文件大小 (字节数):", fileSize);
        processData(arrayBuffer);
      };
      reader.onerror = function (event) {
        console.error("读取文件错误:", event.target.error);
      };
      reader.readAsArrayBuffer(selectedFile);
    } else {
      fileNameDisplay.textContent = "没有选择文件";
    }
  });
  fileInput.click();
}

// 处理二进制数据
function processData(arrayBuffer) {
  const dataView = new DataView(arrayBuffer);
  let hexString = "";
  for (let i = 0; i < dataView.byteLength; i++) {
    const byte = dataView.getUint8(i).toString(16).padStart(2, "0");
    hexString += byte;
  }
  const hexArray = [];
  for (let j = 0; j < hexString.length; j += 2) {
    const hex = hexString.substr(j, 2);
    hexArray.push(hex);
  }
  console.log("所选文件的十六进制字符串:", hexArray);
  flash_program(hexArray, 0)
}

async function flash_program(bin_file, addr) {
  let clc = Math.floor(bin_file.length / 256);
  let serialport_data = [];
  let offset_address = addr;
  console.log("循环次数:", clc);
  if (clc > 0) 
  {
    for (let i = 0; i < clc; i++) {
      for (let j = 0; j < 256; j++) {
        serialport_data.push(bin_file[j + (i * 256)])
      }
      console.log("SendMultipleDatala串口数据长度", serialport_data.length);
      console.log("循环次数", i);
      await flash_page_program("0x0a", offset_address, serialport_data.length, serialport_data);
      serialport_data = [];
      offset_address = ((i + 1) * 256).toString(16);
    }
    programLast_dataLength = bin_file.length - 256 * clc;
    for (let k = 0; k < programLast_dataLength; k++) {
      serialport_data.push(bin_file[(256 * clc) + k]);
    }
    console.log("last串口数据长度", serialport_data.length)
    await flash_page_program("0x0a", offset_address, serialport_data.length, serialport_data);
    lastProgram_flag = true;
    serialport_data = [];
  } else {
    programLast_dataLength = bin_file.length
    for (let i = 0; i < bin_file.length; i++) {
      serialport_data.push(bin_file(i))
    }
    console.log("串口数据长度", serialport_data.length);
    await flash_page_program("0x0a", offset_address, serialport_data.length, serialport_data);
    lastProgram_flag = true;
    serialport_data = [];
  }
}

async function flash_page_program(command, offset_address, length, data) {
  let length_16 = length.toString(16);
  let bytes = `${offset_address},${length_16},${data.join('')}`;
  let bytes2 = `${offset_address},${length_16}`;
  await new Promise((resolve, reject) => {
    setTimeout(async () => {
      try {
        SendMultipleData("0x0a", bytes);
        resolve();
      } catch (error) {
        reject(error);
      }
    }, 300); 
  });
  await new Promise((resolve, reject) => {
    setTimeout(async () => {
      try {
        SendMultipleData("0x0d", bytes2);
        resolve();
      } catch (error) {
        reject(error);
      }
    }, 300);
  });
}

async function flash_init(command, data){
  await SendMultipleData(command, `${data}`);
}

async function flash_chip_erase(command, data){
  await SendMultipleData(command,`${data}`);
}

function clearWindow() {
	console.log("clear");
	document.getElementById("receiverText").textContent = "欢迎使用网页版串口助手。";
}