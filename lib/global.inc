<?php
ini_set('date.timezone','Asia/Shanghai');

$domain     = $_SERVER['HTTP_HOST'];
$base_path  = explode('/', substr(dirname($_SERVER['PHP_SELF']), 1));
$base_path  = $base_path[0];
$protocal   = 'http://';

if(preg_match('/www.[A-Za-z0-9]/', $domain)){
  $domain_type = 'online';
}else {
  $domain_type = 'local';
}

if(isset($base_path)) {
  if($domain_type == 'online') {
    $base_url = $protocal.$domain;
  }else {
    $base_url = $protocal.$domain.'/'.$base_path;
  }
}else {
  $base_url = $protocal.$domain;
}

/* 页面标题 */
$site_name          = '植物365 | 了解你身边的植物 zhiwu365.com - 趣味植物分类查看';
$page_title         = '植物365';
$meta_keywords      = '植物, 植物欣赏, 植物科普, 植物图片, 植物知识, 植物保护, 植物分类, 趣味植物';
$meta_description   = '植物365， 一个提供植物科普知识及相关图文内容的网站。 对植物进行趣味的分类和精简的展示，了解你身边的植物从这里开始。';

/* Store UTF8 file */
define('FILE_UTF8',         "\xEF\xBB\xBF");

define('PREG_FILTER_NOTE',  "/#.*/");

/* Breakline choose, windows or linux */
$os = (DIRECTORY_SEPARATOR=='\\')? false : true;
if($os) {
  define('BREAKELINE', "\n");
  define('BREAKLINE', "\n");
}else {
  define('BREAKELINE', "\r\n");
  define('BREAKLINE', "\r\n");
}

/* Directory separator */
define('OS_SLASH', DIRECTORY_SEPARATOR);

/* How many pages show on page list */
define('PAGER_LIMIT', 20);

/* 图片上传路径 */
define('UPLOAD_PATH',  DOCUMENT_ROOT.OS_SLASH.'uploads');

require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'common.inc';
require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'file.inc';
require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'page.inc';
require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'unicode.inc';
require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'taxonomy.inc';
require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'db.inc';
require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'image.inc';
require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'theme.inc';
?>