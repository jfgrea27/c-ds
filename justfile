# Build the main program
build:
    gcc -g -Isrc/include -Isrc/*/include \
        src/main.c \
        src/*/*.c \
        -o build/main

# Run the main program
run: build
    ./build/main

# Build all tests
build-tests:
    #!/bin/bash
    for module in src/*/; do
        module_name=$(basename $module)
        if [ -d "test/$module_name" ]; then
            echo "Building tests for $module_name..."
            gcc -Isrc/include -Isrc/*/include \
                -I"$module/include" \
                "$module"/*.c \
                "test/$module_name"/*.c \
                -o "build/test_$module_name"
        fi
    done

# Build tests for a specific module
build-test module:
    #!/bin/bash
    if [ -d "test/{{module}}" ]; then
        echo "Building tests for {{module}}..."
        gcc -Isrc/include -Isrc/*/include \
            -Isrc/{{module}}/include \
            src/{{module}}/*.c \
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

clean:
    rm -f build/test_* build/main

