<?php

/* Image max width */
define('IMAGE_MAX_WIDTH', 700);

/* Image thumb width and height */
define('IMAGE_THUMB_WIDTH', 180);
define('IMAGE_THUMB_HEIGHT', 150);

/* 缩略图宽度和高度 */
define('THUMBNAIL_WIDTH', 220);
define('THUMBNAIL_HEIGHT', 230);

/* 默认缩略图宽度和高度 */
define('THUMBNAIL_DEFAULT_WIDTH', 190);
define('THUMBNAIL_DEFAULT_HEIGHT', 200);

/* 缩略图 扩展名 */
define('THUMBNAIL_NAME', '_thumb');

/* 默认缩略图 扩展名 */
define('THUMBNAIL_DEFAULT_NAME', '_thumbnail');

/* 允许图片类型*/
define('ALLOW_IMAGE_TYPE', 'jpg');

function image_upload($thumb = true){
  $view_path  = BLOG_PLANT_IMAGE_PATH;
  $store_path = BLOG_PLANT_IMAGE_FULL_PATH;

  $return = false;

  $upload_file = NULL;
  $destination = NULL;


  if(count($_FILES)) {
    $upload_file = $_FILES;

    $file_type = $upload_file['filename']['type'];
    $file_old_name = $upload_file['filename']['name'];
    $file_tmp_name = $upload_file['filename']['tmp_name'];
    $file_error = $upload_file['filename']['error'];
    $file_size = $upload_file['filename']['size'];

    if($file_size > 3000000) {
      echo 'Error: Upload file is too big false!!!!! (3MB max)';
      return $return;
    }

    if($file_type == 'image/jpeg' | $file_type == 'image/gif'){
      $extend_filename = '.'.end(explode(".", $file_old_name));
    }else{
      echo 'Error: Upload file type false!!!!! (jpeg or gif)';
      return $return;
    }


    $destination = $store_path.OS_SLASH.$file_old_name;

    /* check if image widhh > 700 */
    image_max_resize($file_tmp_name);

    if(move_uploaded_file($file_tmp_name, $destination)) {
      echo 'Upload file successful!';

      $return['image'] = $view_path.'/'.$file_old_name;
    }else {
      echo 'Error: Upload file false!!!!!';
    }

    /* create thumb jpg or not*/
    if($thumb) {
      $image_path['store'] = $store_path;
      $image_path['full'] = $destination;
      $image_path['filename'] = $file_old_name;

      $return['image_thumb'] = $view_path.'/'.image_create_thumb($image_path);
    }
  }

  return $return;
}

function image_create_thumb($image_path=NULL){

  if(is_array($image_path) && count($image_path)) {

    // The file
    $filename = $image_path['full'];

    // Get new dimensions
    list($width, $height) = getimagesize($filename);

    $multipleW = round($width / IMAGE_THUMB_WIDTH, 2);
    $multipleH = round($height / IMAGE_THUMB_HEIGHT, 2);

    if($multipleW > $multipleH){
      $multiple = $multipleW;
    }else {
      $multiple = $multipleH;
    }

    $new_width = round($width / $multiple);
    $new_height = round($height / $multiple);

    // Resample
    $image_p = imagecreatetruecolor($new_width, $new_height);
    $image = imagecreatefromjpeg($filename);
    imagecopyresampled($image_p, $image, 0, 0, 0, 0, $new_width, $new_height, $width, $height);

    $file_name = explode('.', $image_path['filename']);
    $image_thumb_path = $image_path['store'] .OS_SLASH. $file_name[0].'_thumb'.'.jpg';

    // Output
    imagejpeg($image_p, $image_thumb_path, 100);
    echo '<br>Creat image thumb successful!<br>';

    return $file_name[0].'_thumb'.'.jpg';
  }
}

function image_max_resize($image, $image_old_wdith = IMAGE_MAX_WIDTH){
  list($width, $height) = getimagesize($image);

  if($width > $image_old_wdith){
    $percentW = $image_old_wdith / $width;
    $new_width = $width * $percentW;
    $new_height = $height * $percentW;
    $imageDest = imagecreatetruecolor($new_width, $new_height);
    $imageSource = imagecreatefromjpeg($image);
    imagecopyresampled($imageDest, $imageSource, 0, 0, 0, 0, $new_width, $new_height, $width, $height);

    imagejpeg($imageDest, $image, 100);
  }
}

/**
 * Check image store floder exist or not. if not, make it.
 * @param string $name
 * @param string $type 'plant / vocabulary / taxonomy'
 * @return image store path / false
 */
function image_check_store_floder($name, $type='plant') {
  $floder_exist = false;

  $nameEncrypt = plant_encrypt($name);

  switch($type){
    case'plant':
      $path = PLANT_IMAGE_FULL_PATH.OS_SLASH.$nameEncrypt;
      break;
    case'vocabulary':
      $path = VOCABULARY_IMAGE_FULL_PATH.OS_SLASH.$nameEncrypt;
      break;
    case'taxonomy':
      $path = TAXONOMY_IMAGE_FULL_PATH.OS_SLASH.$nameEncrypt;
      break;
  }

  if (file_exists($path)) {
    $floder_exist = $path;
  } else {
    $floder_exist = file_make_floder($path);
  }

  return $floder_exist;
}

function image_get_store_path($name, $type='plant'){
  $nameEncrypt = plant_encrypt($name);
  switch($type){
    case'plant':
      $path = PLANT_IMAGE_FULL_PATH.OS_SLASH.$nameEncrypt;
      break;
    case'vocabulary':
      $path = VOCABULARY_IMAGE_FULL_PATH.OS_SLASH.$nameEncrypt;
      break;
    case'taxonomy':
      $path = TAXONOMY_IMAGE_FULL_PATH.OS_SLASH.$nameEncrypt;
      break;
  }

  return $path;
}

function image_rename($filename, $newname){
  $filenameArray = explode($filename);
  rename();
}

/**
 * 创建缩略图
 * @param 源图片        $source_picture
 * @param 缩略图路径 $thumb_path
 * @param 缩略图宽度 $thumb_width
 * @param 缩略图高度 $thumb_height
 * @return boolean
 */
function image_create_thumb_pic($source_picture, $thumb_path, $thumb_width=THUMBNAIL_WIDTH, $thumb_height=THUMBNAIL_HEIGHT){
    
    /*获取图片信息*/
    list($img_width, $img_height, $img_type, $img_attr) = getimagesize($source_picture);
    
    /* 比例计算, 宽 > 高 或 宽 < 高 */
    if($img_width > $img_height){
        $narrow_percentage = round($thumb_width/$img_width, 2);
    }else{
        $narrow_percentage = round($thumb_height/$img_height, 2);
    }
    
    $narrow_width  = $img_width * $narrow_percentage;
    $narrow_height = $img_height * $narrow_percentage;
    
    // Resample
    $image_p = imagecreatetruecolor($narrow_width, $narrow_height);
    $image = imagecreatefromjpeg($source_picture);
    imagecopyresampled($image_p, $image, 0, 0, 0, 0, $narrow_width, $narrow_height, $img_width, $img_height);
    ImageDestroy($image);
   
    /* 输出图片 */
    if(imagejpeg($image_p, $thumb_path, 100)){
        return true;
    }else{
        return false;
    }
     
}
?>