# 添加 MySQL APT 仓库
wget https://dev.mysql.com/get/mysql-apt-config_0.8.29-1_all.deb
sudo dpkg -i mysql-apt-config_0.8.29-1_all.deb
# 在弹出的界面中选择 OK

# 更新包列表
sudo apt update

# 卸载旧版本（如果已安装）
sudo apt remove libmysqlcppconn-dev

# 安装新版本（包含 X DevAPI）
sudo apt install libmysqlcppconn9-dev