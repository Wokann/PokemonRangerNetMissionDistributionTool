#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 16
#define MAX_ITEMS_PER_LINE 16

void processFile(const char *inputFilename) {
    FILE *inputFile, *outputFile;
    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;
    int itemsWritten = 0;

    // 打开输入文件
    inputFile = fopen(inputFilename, "rb");
    if (inputFile == NULL) {
        printf("无法打开文件或文件不存在。\n");
        return;
    }

    // 构造输出文件名
    char outputFilename[100];
    sprintf(outputFilename, "%s.txt", inputFilename);

    // 打开输出文件
    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("无法创建输出文件。\n");
        fclose(inputFile);
        return;
    }

    fprintf(outputFile, "unsigned char dataArray[] = {");

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, inputFile)) > 0) {
        for (size_t i = 0; i < bytesRead; i++) {
            if (itemsWritten % MAX_ITEMS_PER_LINE == 0)
                fprintf(outputFile, "\n    ");

            // 输出数据
            fprintf(outputFile, "0x%02X,", buffer[i]);

            itemsWritten++;
        }
    }

    fprintf(outputFile, "\n};\n");

    printf("转换完成，结果已保存到 %s 文件中。\n", outputFilename);

    // 关闭文件
    fclose(inputFile);
    fclose(outputFile);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("请将文件拖到此可执行文件上以进行转换。\n");
        return 1;
    }

    // 逐个处理拖拽的文件
    for (int i = 1; i < argc; ++i) {
        processFile(argv[i]);
    }

    return 0;
}
