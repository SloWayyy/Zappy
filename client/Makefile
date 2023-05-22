BUILD_DIR		=	cmake-build-debug
CMAKE_FLAGS		=	-G "Unix Makefiles"

NAME			=	zappy_gui

all: build/$(NAME)

build:
	mkdir -p $(BUILD_DIR)

build/Makefile: $(BUILD_DIR)
	cd $(BUILD_DIR) && $(RM) CMakeCache.txt && cmake $(CMAKE_FLAGS) ..

build/$(NAME): build/Makefile
	$(MAKE) -C $(BUILD_DIR)

$(NAME): build/$(NAME)
	cp $(BUILD_DIR)/$(NAME) .

clean:
	$(MAKE) -C $(BUILD_DIR) clean

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re