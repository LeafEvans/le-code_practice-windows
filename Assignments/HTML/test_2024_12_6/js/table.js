// 新增数据函数
function addRow() {
  let table = document.getElementById("table");
  // console.log(table);
  // 获取插入的位置
  let length = table.rows.length;
  // console.log(length);
  // 插入行节点
  let newRow = table.insertRow(length);
  console.log(newRow);

  // 插入列节点
  let nameCol = newRow.insertCell(0);
  let phoneCol = newRow.insertCell(1);
  let optionCol = newRow.insertCell(2);

  // 修改节点文本内容
  nameCol.innerHTML = "未命名";
  phoneCol.innerHTML = "无联系方式";
  optionCol.innerHTML =
    '<button onclick="editRow(this)">编辑</button><button onclick="deleteRow(this)">删除</button>';
}

// 删除数据函数
function deleteRow(button) {
  // console.log(button);
  let row = button.parentNode.parentNode;
  console.log(row);
  row.parentNode.removeChild(row);
}

// 编辑数据函数
function editRow(button) {
  // console.log(button);
  let row = button.parentNode.parentNode;
  let name = row.cells[0];
  let phone = row.cells[1];

  let inputName = prompt("请输入名字：");
  let inputPhone = prompt("请输入联系方式：");

  name.innerHTML = inputName;
  phone.innerHTML = inputPhone;
}
