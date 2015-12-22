<?php

/**
 * 获取给定路径下的所有包含"_"的文件和文件夹名字.
 * @return array()
 */
function file_get_folder_names($path){

   $folder_names = array();
   if ($handle = @opendir($path)) {
    while (false !== ($file = readdir($handle))) {
//      if(strstr($file, '_')) {
//         $folder_names[] = $file;
//      }
      if(preg_match('/[^\.]/', $file) && $file != 'img' && $file !='.svn') {
         $folder_names[] = $file;
      }
    }
    closedir($handle);

    sort($folder_names);

    return $folder_names;
  }else {
    echo 'Error! can not open dir! '.$path;
    return false;
  }
}

/**
 * 获取给定路径下的所有不包含".和img"的文件和文件夹名字. 读取blog文章专用.
 * @return array()
 */
function file_get_file_names($path){
   $folder_names = array();
   if ($handle = @opendir($path)) {
    while (false !== ($file = readdir($handle))) {
      if(preg_match('/[^\.]/', $file) && $file != 'img') {
         $folder_names[] = $file;
      }
    }

    /* 重新排序, 最新添加的blog排在前面 */
    rsort($folder_names);

    closedir($handle);
    return $folder_names;
  }else {
    echo 'Error! can not open dir!';
    return false;
  }
}


/**
 * 去掉微软文本编辑器自动加上的file_handle_UFT8(xEFxBBxBF), 为区别UTF8文件.
 */
function file_handle_UFT8($file){
  return $file = preg_replace("/\xEF\xBB\xBF/", NULL, $file);
}

/**
 * 去掉文件里的注释部分" #note "
 */
function file_filter_note($file) {
  return preg_replace(PREG_FILTER_NOTE, NULL, $file);
}

/**
 * 转换Ascii码 成为HTML
 * @ 空格 => "&nbsp;"
 * @ 换行符 => "<br>"
 */
function file_handle_ascii_to_html($content) {
  $content = html_entity_decode(str_replace(' ', '&nbsp;', $content), ENT_QUOTES, 'UTF-8');
  $content = nl2br(htmlspecialchars($content));
  return $content;
}

/**
 * 去掉文件夹名字里面的"数字_", 直接返回后面的名字
 * @param string $name
 */
function file_filter_floder_name($floder_name) {
   return substr(strstr($floder_name, '_'), 1);
}

/**
 * 创建或者全部更新单个文件.
 */
function file_create_file($path, $content){
  $fp=fopen($path,'w+');
  if(fwrite($fp,$content)){
    $return = true;
  }else{
    $return = false;
  }
  fclose($fp);

  return $return;
}

/**
 * 创建多个文件夹.
 */
function file_create_folders($foldernames, $perm = 0777){
  foreach($foldernames AS $foldername){
    if (file_exists($foldername)) {
        echo "The folder $foldername exists<br>";
    } else {
      if(mkdir($foldername, $perm)){
          echo 'Good folder! - '.$foldername.'<br>';
      }else{
         echo 'Bad folder. - '.$foldername.'<br>';
      }
    }
  }
}

/**
 * 创建多个文件 (如果文件存在, 删除文件内所有内容).
 */
function file_create_files($files, $perm = 0777){
  foreach($files AS $path => $content){
    $result_info = fopen($path, 'w');
    $content=FILE_UTF8.$content;
    if (fputs($result_info, $content) === FALSE) {
      echo "Bad file. - $path".'<br>';
    }
    echo "Good file! - $path".'<br>';
    fclose($result_info);
  }

//  chmod($filename, $perm);
}

/**
 * 更新索引文件, 在文件末尾新插入一行.
 */
function file_update_index($path, $content){
  if (is_writable($path)) {
    if (!$handle = fopen($path, 'a')) {
         echo "不能打开文件 $path";
         exit;
    }
    if (fwrite($handle, $content) === FALSE) {
        echo "不能写入到文件 $path";
        exit;
    }

    echo "更新成功!!! $path <br>";

    fclose($handle);
  } else {
    echo "文件 $path 不可写";
  }
}
?>