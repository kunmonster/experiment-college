# 大素数判定

# Miller Rabbin

* 费马小定律 
  > 如果p为质数(素数),且a,p互质<font color="red">(a,b最大公约数为1)</font>,则存在 **a^(p-1)≡1(mod p) 即 (p|a^(p-1)-1)即a^(p-1) % p == 1**
* 定理2
  > 如果P是一个质数,那么对于x(0&lt;x&lt;p),**若x^2 mod p == 1,则x == 1 或 p-1**
