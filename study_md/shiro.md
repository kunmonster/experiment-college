## shiro 核心组件

> 用户获取角色,角色拥有权限

1. 	UsernamePasswordToken,Shiro用来封装用户登录信息,使用用户的登录信息来创建令牌

2. 	SecurityManage,Shiro的核心部分,负责安全认证和授权

3. 	Subject,Shiro的一个抽象概念,包含用户信息

4. 	Realm,开发者自定义的模块,根据项目的需求,验证和授权的逻辑全部写在Realm中

5. 	AuthenticationInfo,用户角色信息集合(认证时使用)

6. 	AuthorzationInfo,角色权限信息,授权时使用

7. DefaultWebSecurityManage,安全管理器,开发者自定义的Realm需要注入到此处进行管理才能生效

8. ShiroFilterFactoryBean,过滤器工厂,Shiro的基本运行机制是开发者制定规则,Shiro去执行,具体执行操作就是该工厂完成

## shiro使用+Spring boot
1. 自定义Shiro过滤器
2. 认证过滤器--过滤规则
	* anon:无需认证
	* authc:必须认证
	* authcBsae:需要通过HTTPBasic认证
	* user:不一定通过认证,只要曾经被Shiro记录即可,比如:记住我

3. 授权过滤器
	* perms:必须拥有某个权限才能访问
	* role:必须拥有某个角色才能访问
	* port:请求的端口必须是指定值
	* rest:请求必须基于RESTful,post,put,get,delete等
	* ssl:必须是安全的URL请求,协议HTTPS

## 流程--认证
1. 收集用户身份/凭证,即用户名,密码
2. 调用Subject.login()进行登录,如果失败将得到相应的AuthenticationException异常,根据异常提示用户信息,否则登陆成功
3. 创建自定义的Realm类,继承AuthenticatingRealm实现doGetAuthenticationInfo()方法

## 流程--授权
1. subject.isPermitted*/hasRole(判断有没有权限)向下委托给SecurityManage中的authorizer
2. Authorizer是真正的授权者,如调用isPermitted("user:view")会先通过PermissionResolver把字符串转换相应的Permission实例
3. 在进行授权之前,会调用相应的Realm获取Subject相应的角色/权限用于匹配传入的角色/权限
4. Authorizer会判断Realm的角色/权限是否和传入的匹配,如果有多个Realm会委托给ModularRealmAuthorizer进行循环判断,如果匹配如IsPermitted*/hasRole*会返回true,否则返回false表示授权失败