##vue router
1. 使用场景
	* 在单页应用中实现类似路由的跳转功能

## vue 实例与数据相关
1. 当实例被创建时已经存在于data中的property才是响应式的,也就是说如果你添加一个新的property那么对该property改动将不会触发视图更新

2. Object.freeze()会阻止修改现有的property,也意味着响应系统无法再追踪变化

3. 前缀$用来与用户定义的property区分开来

4. 实例生命周期钩子
	* new Vue()
	* beforeCreate
	* created:用于一个实例被创建后执行代码
	* has " el "option?
	* has "template" option?
	* 如果没有template选项,则编译el的html为template,如果有template,那么将template编译进渲染方法中
	* beforeMount()
	* 创建vue.$el并用用它替换el
	* mounted
	* 当data中数据改变的时候,beforeupdate->virtualDom重新渲染->updated
	* beforeDestory()
	* 摧毁watcher,childre components和事件监听
	* Destoryed

5. 不要在property或者回调时使用箭头函数,因为箭头函数没有this对象

6. 插值
	* 文本--数据绑定--双大括号,使用v-once将会进行一次性插值,当数据改变的时候也不会更新,但是会影响该节点上的其他数据绑定
	* 原始HTML---为了输出真正的HTML可以使用v-html(不要对用户提供的内容使用插值,小心xss)
	* attribute---在属性上使用插值,需要使用v-bind指令,对于布尔类型的属性,只要显式写出就表示true
	* javascript

7. 指令
	* 带有v-前缀的attribute就是指令，指令的作用为,当表达式的值改变时,将其产生的连带影响，响应式地作用于DOM
	* v-bind可以用于响应式地更新HTML-attribute
	* v-on用于监听DOM事件
	* 动态参数--v-bind:[attributeName]="",这里地attribute会被当成js表达式动态求值,求得的值会作为参数(冒号后面),v-on也可以使用
	* 动态参数预期会求出一个字符串,异常情况为null,这个特殊地null可以被显性地用于移除绑定。任何其他非字符串类型的值都会触发一个警告
	* 在动态参数中使用空格，引号无效
	* 修饰符
		1. 修饰符是以半角符号.指明的特殊后缀,用于指出一个指令应该以特殊方式绑定,例如.prevent修饰告诉v-on指令对于触发的事件调用event.preventDefault()
	* v-bind:缩写----冒号
	* v-on:缩写@

8. 计算属性和侦听属性
	* 计算属性
		1. 语法
			```vue.js
			computed:{
           	//后面的方法就是计算属性的getter
            属性名字:function(){
           		return 与某个数据相关
            	}
            }
            ```
		2. 计算属性是基于他们响应式依赖进行缓存的,只在相关响应式依赖发生改变时才会重新求值,意味这message还没发生改变的时候多次访问计算属性会立即返回之前使用过的结果,不必再次执行函数
		3. setter
			* 计算属性默认只有getter()
			* 可以在需要的时候提供setter
			```vue.js
			computed:{
           	//后面的方法就是计算属性的getter
            data数据名字:{
            		//getter
            		get:function(){}
            		//setter
                    set:function(newValue){}
                }
            }
            ```
    * 侦听属性--watch
    	1. 通常使用计算属性而不是使用watch回调
    	```vue.js
    	watch:{
        	data中的属性名:function(){} //回调方法
        }
        ```

	* 侦听器
		1. 可以完成异步的操作,计算属性无法做到



9. v-bind:class对class支持数组和对象类型
	* 使用计算属性返回值
	* 使用数组

10. 用在组件上
	* 在组件上使用class将对组件内部的标签全部有效

11. 绑定内联样式
	* v-bind:style="{}"
	* 同样可以使用数组和对象语法
	* 绑定内联样式的时候会自动加上css前缀
	* 多重值
		1. 可以为style绑定中的property提供一个包含多个值的数组,常用于提供多个带前缀的值


12. v-if可以加上v-else
13. v-if必须添加到一个元素上,但是如果想切换多个元素,此时可以把一个template元素当作不可见的包裹元素,并在上面使用v-if,最终结果将不包含 < template >元素

14. 用key管理可复用的元素
	* vue会尽可能高效的渲染元素,通常会复用已有元素而不是从头开始渲染,这么做除了使Vue变得非常快之外,还有其他好处---如果允许用户在不同的登录方式之间切换
	* 添加key将会使得元素完全独立,不要复用他们,但是没添加key的将会复用

15. v-show
	* 与v-if大致一样,但是带有v-show的元素始终渲染并保留在DOM中。v-show只是简单切换元素的可见性(css-display:none/block)
	* v-show不支持 < template > 也不支持v-else

16. v-if与v-show
	* v-if是惰性的，如果在初始时候条件为假,什么也不做，直到第一次条件变为真
	* v-show不管条件是什么,元素总是会被渲染,并且只是简单进行css切换
	* v-if拥有较高的切换开销,当切换频繁的时候使用v-show

17. v-if与v-for一起使用
	* 不推荐v-if和v-for一起使用
	* 当两者一起使用的时候v-for拥有较高的优先级

18. 列表渲染--v-for
	* v-for块中可以访问父作用域的property
	* v-for还支持一个可选的第二个参数,即当前项的索引v-for="(item,index) in array"
	* v-for也可以作用于对象,此时第二个参数可以为见name(键名),还可以添加第三个参数为索引
	* 当vue正更新使用v-for渲染的元素列表时,默认使用就地更新策略,如果数据项的顺序改变,Vue将不会移动DOM来匹配顺序的改变,而是就地更新每个元素,并且确保他们在每个索引位置正确渲染

19. 数组更新检测
	* 变更方法--下述方法也会触发视图更新
		1. push()
		2. pop()
		3. shift()
		4. unshift()
		5. splice()
		6. sort()
		7. reverse()
	* 替换数组---替换旧数组(不会变更原数组,总是返回新数组)
		1. filter()
		2. concat()
		3. slice()




## axios的基本使用
1. 