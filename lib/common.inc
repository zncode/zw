<?php

/**
 * 格式化链接
 */
function l($text, $path=NULL, $options = array()) {
  global $base_url;
  $target = NULL;

  if(empty($path)){
    $path = '';
  }else {
    $path = url($path);
  }

  if(@$options['class']){
    $class = $options['class'];
  }else {
    $class = NULL;
  }

  if(@$options['target']){
    $target = $options['target'];
  }

  if($target){
    $l = '<a href="'.$path.'" class="'.$class.'" target="'.$target.'" >'. $text .'</a>';
  }else {
    $l = '<a href="'.$path.'" class="'.$class.'" >'. $text .'</a>';
  }

  return $l;
}

/**
 * 翻译函数
 */
function t($text){
  return $text;
}

/**
 * 获取路径?q= 后面的URL.
 */
function request_path() {
  if (isset($_GET['q'])) {
    // This is a request with a ?q=foo/bar query string. $_GET['q'] is
    // overwritten in drupal_path_initialize(), but request_path() is called
    // very early in the bootstrap process, so the original value is saved in
    // $path and returned in later calls.
    $path = $_GET['q'];

    if(preg_match("/[&]/", $path)){
      $path = explode('&', $path);
      $path = $path[0];
    }
  }
  elseif (isset($_SERVER['REQUEST_URI'])) {

    // This request is either a clean URL, or 'index.php', or nonsense.
    // Extract the path from REQUEST_URI.
    $request_path = strtok($_SERVER['REQUEST_URI'], '?');
    $base_path_len = strlen(rtrim(dirname($_SERVER['SCRIPT_NAME']), '\/'));
    // Unescape and strip $base_path prefix, leaving q without a leading slash.
    $path = substr(urldecode($request_path), $base_path_len + 1);

    if(preg_match("/[&]/", $path)){
      $path = explode('&', $path);
      $path = $path[0];
    }

    // If the path equals the script filename, either because 'index.php' was
    // explicitly provided in the URL, or because the server added it to
    // $_SERVER['REQUEST_URI'] even when it wasn't provided in the URL (some
    // versions of Microsoft IIS do this), the front page should be served.
    if ($path == basename($_SERVER['PHP_SELF'])) {
      $path = '';
    }
  }
  else {
    // This is the front page.
    $path = '';
  }

  // Under certain conditions Apache's RewriteRule directive prepends the value
  // assigned to $_GET['q'] with a slash. Moreover we can always have a trailing
  // slash in place, hence we need to normalize $_GET['q'].
  $path = trim($path, '/');

  return $path;
}

/**
 * 获取URL参数，把路径分割成数组，然后返回。
 */
function arg($path=NULL){
  if(!isset($path)) {
    $path = request_path();
  }

  /* filter path */
  str_replace('<', ' ', $path);
  str_replace('>', ' ', $path);
  $path = trim($path);

  $arguments = explode('/', $path);
  return $arguments;
}

/**
 * 页面跳转
 */
function page_goto($path, $query = NULL, $fragment = NULL, $http_response_code = 302){
  $url = url($path);
  header('Location: ' . $url, TRUE, $http_response_code);
  exit();
}

/**
 * 生成完整页面访问路径.
 */
function url($path) {
  global $base_url;

  if(preg_match('/http:/i', $path)){
    $url = $path;
  }else{
    $url = $base_url.'/'.$path;
  }

  return $url;
}


/**
 * 格式化日期时间
 */
function format_date($timestamp) {
  return date('Y-m-d H:i', $timestamp);
}

/**
 * 调试函数
 */
function debug($file){
  print_r($file);
  die();
}

function html_content($content, $image_path=NULL){
  global $base_url;

  //替换制表符
  $content = preg_replace('/\t/', '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;',$content);

  //替换' '
  $content = html_blankspace_replace($content);

  //替换换行符
  $content = nl2br($content);

  //替换文章图片路径 (__ARTICLE_IMAGE_PATH__)
  if($image_path) {
    $article_image_path = $base_url.'/articledata/'.$image_path.'/images';

    $content = preg_replace('/__AIP__/', $article_image_path, $content);
  }

  return $content;
}

function html_blankspace_replace($str){
  $str_arr = preg_split ("/<[^>]*>/", $str,-1,PREG_SPLIT_OFFSET_CAPTURE);
  foreach($str_arr AS $k => $v){
    if(isset($str_arr[$k+1]))
    {
        $temp        = $str_arr[$k][1] + strlen($str_arr[$k][0]);
        $str_arr[$k][2]    = substr($str, $temp, $str_arr[$k+1][1] - $temp);
    }
  }

  foreach($str_arr as $key=>$value){
    if($value!='') {
      $temp=$value[0];
      $str_arr[$key][0]=str_replace(" ","&nbsp;",$temp);
    }
  }

  foreach($str_arr AS $k => $v){
    unset($v[1]);
    $str_arr[$k]=implode('',$v);
  }

  $str=implode('',$str_arr);
  return $str;
}

function filter($content){
  $content = check_magic_quotes_gpc($content);
  return $content;
}

function check_magic_quotes_gpc($content){
  if (get_magic_quotes_gpc()) {
    $content = stripslashes($content);
  }
  return $content;
}

function remove_breakline($str){
  $str = trim($str, '\r\n');
 return $str;
}

/**
 * 获取当前完整URL
 * @return string
 */
function get_current_url(){
    return 'http://'.$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
}

function get_request_url(){
    return $_SERVER['REQUEST_URI'];
}
?>