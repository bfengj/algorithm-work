webpackJsonp([5],{t2Q3:function(t,e,l){"use strict";Object.defineProperty(e,"__esModule",{value:!0});var a={name:"TaskList",data:function(){return{tasks:[]}},created:function(){var t=this;this.$axios.get("/api/tasks").then(function(e){t.tasks=e.data,console.log(e.data)}).catch(function(e){t.tasks=[{end_time:1641571469.316159,is_alive:!1,name:"Using shellSort to find the Max!INPUTFILE:100books.json OUTPUTFILE:test3.json X:100",result:"待排序数组长:100\n主循环执行了909次\n总时间：0.00004100s",start_time:1641571469.3019688,uuid:"7e8432c6-6fd3-11ec-bc05-4ee35ea174e5",outputfile:"100books.json"}]})},methods:{delete:function(t){this.$axios.get("/api/deleteTask?uuid="+t.path[4].children[0].children[0].outerText).then(function(){window.location.reload()}).catch(function(){window.location.reload()})},linkToDataTable:function(t,e,l,a,o){"操作"!=e.label&&(window.location.href="/#/dataTable?file="+t.outputfile)},timeToDate:function(t,e,l,a){return l}}},o={render:function(){var t=this,e=t.$createElement,l=t._self._c||e;return l("el-table",{attrs:{data:t.tasks},on:{"cell-click":t.linkToDataTable}},[l("el-table-column",{attrs:{prop:"uuid",label:"uuid",width:"400"}}),t._v(" "),l("el-table-column",{attrs:{prop:"name",label:"任务名称",sortable:"",width:"650"}}),t._v(" "),l("el-table-column",{attrs:{prop:"is_alive",label:"是否进行中",width:"50"}}),t._v(" "),l("el-table-column",{attrs:{prop:"result",label:"输出"}}),t._v(" "),l("el-table-column",{attrs:{prop:"start_time",label:"开始时间",formatter:t.timeToDate}}),t._v(" "),l("el-table-column",{attrs:{prop:"end_time",label:"结束时间",formatter:t.timeToDate}}),t._v(" "),l("el-table-column",{attrs:{prop:"outputfile",label:"输出文件"}}),t._v(" "),l("el-table-column",{attrs:{label:"操作"}},[l("el-button",{attrs:{type:"danger",icon:"el-icon-delete",circle:"",prop:"uuid"},on:{click:this.delete}})],1)],1)},staticRenderFns:[]},n=l("C7Lr")(a,o,!1,null,null,null);e.default=n.exports}});
//# sourceMappingURL=5.de1c6c3e4407c97506f7.js.map