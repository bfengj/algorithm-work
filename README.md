## 前言

算法设计综合实验课程的大作业。前端由学长完成，我和另外一个学长负责C语言实现的各种算法以及解决问题。

## 目录结构

- algo
  - cpp   **排序算法设计实现存放目录**

  - web **python-flask实现的后端存放目录**

    - static  **前端页面所需要的静态资源存放目录**
    - templates **前端模板存放目录存放目录**
    - lib **接口文件，包括数据生成以及调用cpp编译的可执行文件**

    - app.py **主程序**
## 使用说明

首先使用`pip install -r requirements.txt`安装`flask`(web后端框架)、`faker`（假数据生成）、tqdm（命令行进度条）依赖。

之后直接`python app.py`将会在本地开放一个8082端口提供web服务。

url:http://127.0.0.1:8082/

