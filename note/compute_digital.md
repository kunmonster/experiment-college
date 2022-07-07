
[TOC]



# 定点数运算

## 算术(保持数学的意义,有符号数的移位)移位

<font color="red">不改变符号位</font>
<table>
<tr>
<td></td>
<td>码制</td>
<td>添补代码</td>
</tr>
<tr>
<td>正数</td>
<td>原码、反码、补码</td>
<td>0</td>
</tr>
<tr>
	<td rowspan="5">负数</td>
</tr>
<tr>
<td>原码</td>
<td>0</td>
</tr>
<tr>
<td rowspan="2">补码</td>
<td>右移高位补1</td>
</tr>
<tr>
<td>右移低位补0</td>
</tr>
<tr>
<td>反码</td>
<td>1</td>
</tr>

</table>

## 逻辑移位(无符号的移位,所有数据位均要移位)
+ 逻辑左移 : 低位添0,高位移丢
+ 逻辑右移 : 高位添0,低位移丢

# 溢出判断
