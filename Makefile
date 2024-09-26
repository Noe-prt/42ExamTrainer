all: check_json_lib check_readline_lib compile

check_json_lib:
	@dpkg -s nlohmann-json3-dev > /dev/null 2>&1 || (echo "Installing nlohmann-json..." && sudo apt update && sudo apt install -y nlohmann-json3-dev)

check_readline_lib:
	@dpkg -s libreadline-dev > /dev/null 2>&1 || (echo "Installing libreadline..." && sudo apt update && sudo apt install -y libreadline-dev)

compile:
	@g++ -o app .system/*.cpp -I/usr/include -lreadline
	@chmod +x app

clean:
	@rm -f app

