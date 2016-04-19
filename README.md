# tkd53: かな漢字変換システム

## 使い方
### セットアップ
```
$ git submodule update --init
```

### ビルド
```
$ cd bin && sh ./build.sh
```

### 実行
#### かな漢字変換サーバの実行
```
cd bin && ./main
```

## テスト
tkd53はテストフレームワークに[googletest](https://github.com/google/googletest)を使用しています。

### googletestをインストール
```
$ cd src/third_party/googletest/googletest/build-aux
$ cmake ../
$ make
$ mkdir -p ../../../../../tests/bin/gtest
$ cp libgtest.a libgtest_main.a ../../../../../tests/bin/gtest
```

### テストの実行
例えば、engineのテスト (engine_test) は次にようにして実行します。

```
$ cd src/engine
$ make test
$ cd ../../tests/bin/engine/
$ ./engine_test
```
