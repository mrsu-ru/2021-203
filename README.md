# Введение в выч. методы

## Обновление своего репозитория:

#### 1. ссылка на удаленный репозиторий: 
 git remote add mrsu https://github.com/mrsu-ru/2021-203.git

#### 2. новая ветка (создаем и переключаемся):
 git checkout -b mrsu-master
 
#### 3. затягиваем изменения из удаленного репозитория:
 git pull mrsu master
 
#### 4. переключаемся на ветку master:
 git checkout master
 
#### 5. сливаем ветку mrsu-master в ветку master:
 git merge --no-ff mrsu-master
 
#### 6. проталкиваем изменения в удаленный репозиторий origin:
 git push origin master
 
#### 7. удаляем ветку mrsu-master:
 git branch -d mrsu-master
 
#### 8. смотрим лог изменений:
 git log --graph --decorate --all
 
 
 
