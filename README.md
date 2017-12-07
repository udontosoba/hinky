# Hinky's Robocon Git Repository README File
## Git Repositoryの使い方
### リポジトリの複製方法（自分が決めた作業用フォルダにリポジトリを落とすとき、最初に1回やる操作）
$ git clone https://github.com/udontosoba/hinky.git

マスターブランチがクローン（ローカルに複製）されます

### ブランチの複製方法
$ git checkout -b "ブランチ名" "リモートブランチ名"

例えば、testブランチをクローンする場合

$ git checkout -b test origin/test

### ブランチの確認
$ git branch

\* master

  test

\*の付いてるブランチが今現在いるブランチを示す。

### ブランチの変更（testブランチに移動）
$ git checkout test

ちなみに、testブランチは練習用に作ってあるので自由に色々試してみてください。

### 編集の反映
$ echo "(適当に好きなメッセージを入れる。)" >> README.md

ここではREADME.mdに適当な文を追加して編集したことにします。

$ git add README.md

編集したファイルの編集内容をgitに認識させます。

$ git commit -m "(commit message)"

コミットすることでローカルに反映されます。

commit messageには編集内容が簡単にわかる説明文を入れると良いです。

文字化け対策のため、英語推奨です。

commit messageの例：add stop function, modify go function in go_and_stop.cなど

$ git push

これでやっとローカルにコミットした編集内容がサーバーに反映されます。
