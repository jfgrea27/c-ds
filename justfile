# Build the main program
build: clean
    gcc -O0 -g-Isrc/*/include \
        src/main.c \
        $(ls src/*/*.c | grep -v 'main.c') \
        -o build/main

# Run the main program
run: build
    ./build/main

# Build all tests
build-tests: clean
    #!/bin/bash
    for module in src/*/; do
        module_name=$(basename $module)
        if [ -d "test/$module_name" ]; then
            echo "Building tests for $module_name..."
            gcc -g -Isrc/*/include \
                -I"$module/include" \
                $(ls "$module"/*.c | grep -v 'main.c') \
                "test/$module_name"/*.c \
                -o "build/test_$module_name"
        fi
    done

# Build tests for a specific module
build-test module: clean
    #!/bin/bash
    if [ -d "test/{{module}}" ]; then
        echo "Building tests for {{module}}..."
        gcc -g -Isrc/*/include \
            -Isrc/{{module}}/include \
            $(ls src/{{module}}/*.c | grep -v 'main.c')  \
            test/{{module}}/*.c \
            -o build/test_{{module}}
    else
        echo "No tests found for module {{module}}"
        exit 1
    fi

# Run all tests
run-tests: build-tests
    #!/bin/bash
    for test in build/test_*; do
        if [ -x "$test" ]; then
            echo "Running $test..."
            $test
        fi
    done

# Run tests for a specific module
run-test module: (build-test module)
    ./build/test_{{module}}


build-module module *deps: clean
    gcc -O0 -g -Isrc/{{module}}/include \
        $({for dep in deps: "-Isrc/" + dep + "/include"; done}) \
        src/{{module}}/*.c \
        $({for dep in deps: "src/" + dep + "/*.c"; done} | grep -v 'main.c') \
        -o build/main_{{module}}

# Run specific module main
run-module module: build
    ./build/main_{{module}}

mem-check module: clean
    just build-module {{module}}
    valgrind --leak-check=full --track-origins=yes ./build/main_{{module}}


clean:
    rm -rf build/test_* build/main

