# Makefile for srr2illumina
# FastQ file processor to remove first token from read names

# コンパイラとフラグ
CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99
LDFLAGS = -lz

# ターゲット実行ファイル名
TARGET = srr2illumina

# ソースファイル
SOURCES = srr2illumina.c

# オブジェクトファイル
OBJECTS = $(SOURCES:.c=.o)

# デフォルトターゲット
all: $(TARGET)

# 実行ファイルのビルド
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# オブジェクトファイルのビルド
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# クリーンアップ
clean:
	rm -f $(OBJECTS) $(TARGET)

# インストール（オプション）
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# アンインストール（オプション）
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# 依存関係の確認
check-deps:
	@echo "Checking for required libraries..."
	@pkg-config --exists zlib && echo "✓ zlib found" || echo "✗ zlib not found"

# テスト実行用のヘルプ
help:
	@echo "Available targets:"
	@echo "  all       - Build the program (default)"
	@echo "  clean     - Remove compiled files"
	@echo "  install   - Install to /usr/local/bin"
	@echo "  uninstall - Remove from /usr/local/bin"
	@echo "  check-deps- Check for required dependencies"
	@echo "  help      - Show this help message"
	@echo ""
	@echo "Usage: ./$(TARGET) <input.fastq.gz>"
	@echo "Output: processed FastQ to stdout"

# phonyターゲットの宣言
.PHONY: all clean install uninstall check-deps help
