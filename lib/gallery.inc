<?php
define('GALLERY_DATA_PATH', DOCUMENT_ROOT.OS_SLASH.'gallerydata'.OS_SLASH);
define('GALLERY_CATEGORY_INDEX', DOCUMENT_ROOT.OS_SLASH.'gallerydata'.OS_SLASH.'gallery.index');

define('GALLERY_OVERVIEW_PATH', 'gallery');
define('GALLERY_LIST_PATH', 'gallery/%');

define('GALLERY_PHP_FILE', 'gallery_new.php');
define('GALLERY_SUBMIT_PHP_FILE', 'gallery_new_submit.php');


/**
 * 植物页面显示类
 */
class PageGallery extends Page{

  /**
   * 显示类型
   */
  public $gallery_displaytype = 'overview';

  /**
   * 画册信息
   */
  public $gallery;

  /**
   * 设置画册信息
   */
  public function SetGallery($value){
    $this->gallery = $value;
  }

  /**
   * 设置文章显示类型
   */
  public function SetGalleryDisplayType($value){
    $this->gallery_displaytype = $value;
  }

  /**
   * 显示页面内容
   */
  public function DisplayContent(){
    $displayType = $this->gallery_displaytype;
    switch($displayType){
      case 'category':
        echo '<div class="gallery_category_wrapper">';
        $this->DisplayBreadcrumb();
        $this->DisplayCategory();
        echo '</div>';
        break;
      case 'overview':
        echo '<div class="gallery_overview_wrapper">';
        $this->DisplayBreadcrumb();
        $this->DisplayOverview();
        echo '</div>';
        break;
    }
  }

  /**
   * 显示总览页面
   */
  public function DisplayCategory(){
    global $base_url;

    if($this->pagenotfound === true){
      echo call_user_func('page_not_found');
      return false;
    }

    $gallerys = $this->gallery;

    $output = '<div class="content">';
      $output .= '<ul>';
      if(is_array($gallerys) && count($gallerys)){
        foreach($gallerys AS $gallery){
          $gid = $gallery['id'];
          $piyin = $gallery['piyin'];
          $name = $gallery['name'];
          $image = $base_url.'/uploads/gallery/'.$gid.'_'.$piyin.'/default.jpg';
          $image_thumb = '<a href="'.$base_url.'/gallery/'.$gid.'" target="_blank"><img src="'.$image.'" alt="'.$name.'"/></a><br>';
          $output .= '<li> '.$image_thumb.l($name, 'gallery/'.$gid, array('target'=>'_blank')).' </li>';
        }
      }else {
        $output .= '<li> 暂时无内容 <li>';
      }

      $output .= '</ul>';
    $output .= '</div>';

    echo $output;
  }

  /**
   * 显示总览页面
   */
  public function DisplayOverview(){
    global $base_url;

    if($this->pagenotfound === true){
      echo call_user_func('page_not_found');
      return false;
    }

    $gallery = $this->gallery;
    $gallery_name = $gallery[0]['name'];
    $gallery_description = $gallery[0]['description'];

    $gallery_contents = $gallery[0]['gallery_contents'];

    $output = '<div class="content">';

      /* 标题描述 */
      $output .= '<div class="gallery_title">';
      $output .= $gallery_name;
      $output .= '</div>';
      $output .= '<div class="gallery_description">';
      $output .= $gallery_description;
      $output .= '</div>';

      $output .= '<ul>';
      if($gallery_contents){

        foreach($gallery_contents AS $gallery_content){
          $image_thumb_path = $base_url.'/uploads/gallery/'.$gallery_content['gallery_floder_name'].'/thumb/'.$gallery_content['image_thumb_name'];
          $image_path       = $base_url.'/uploads/gallery/'.$gallery_content['gallery_floder_name'].'/original/'.$gallery_content['image_name'];
          
          $image_thumb = '<a href="'.$image_path.'" target="_blank"><img src="'.$image_thumb_path.'" alt="'.$gallery_content['title'].'"/></a><br>';
          $output .= '<li> '.$image_thumb.l($gallery_content['title'], $image_path, array('target'=>'_blank')).' </li>';

        }
      }else {
        $output .= '<li> 暂时无内容 <li>';
      }

      $output .= '</ul>';
    $output .= '</div>';

    echo $output;
  }


}

/**
 * 显示画册页面
 */
function gallery_display_content($arg){
  global $page_title;
  $pagenotfound = false;
  
  $type = $arg[0];
  
  
  switch($type){
    case 'gallery':
      //检查图册ID
      $gid  = $arg[1];
      if(!empty($gid) && gallery_check_gid_exist($gid)){
        
        $gallery = gallery_load($gid);

        $title = $gallery[0]['name'];
        $meta_keywords = $gallery[0]['keyword'];
        $meta_description = $gallery[0]['description'];
        
        $breadcrumbs[] = array('title'=>$title);
        $gallery_displaytype = 'overview';
      }else{
        $pagenotfound = true;
      }
    break;

    case 'gallery_category':
      $title = '植物图册';
      $meta_keywords = '植物图册';
      $meta_description = '植物图册分类查看';
      $breadcrumbs[] = array('title'=>'植物图册');
      $gallery = gallery_load();
      $gallery_displaytype = 'category';
    break;
  }

  $page = new PageGallery();

  if($pagenotfound){
    $page->SetPagenotfound($pagenotfound);
    $page->SetTitle('页面没有找到');
  }else{
    $page->SetGalleryDisplayType($gallery_displaytype);
    $page->SetTitle($title.'_'.$page_title);
    $page->SetMetaKeywords($meta_keywords);
    $page->SetMetaDescription($meta_description);
    $page->SetGallery($gallery);
    $page->SetBreadcrumb($breadcrumbs);
  }

  $page->DisplayPage();
}

/**
 * 读取图片
 * 1. 读取gallery.index文件，获取目录信息.
 * 2. 读取image.index文件, 获取图片名字, 以及ID号
 * 3. 组合路径, 遍历所有文件夹获取内容，以及图片地址.
 * @retrun array()
 */
function gallery_load($gid=NULL){
    global $base_url;
    $db = new database;
    
    $gallerys = false;
    
    //表路径
    $table_gallery = DB_PATH.TABLE_GALLERY;
    $table_gallery_content = DB_PATH.TABLE_TAXONOMY_CONTENT_GALLERY;
    
    if($gid){
        $where = array('id'=>$gid);
        $gallerys  = (array)$db->db_select($table_gallery, $where);
    }else{
        $where = '';
        $gallerys  = (array)$db->db_select($table_gallery, $where);
        $gallerys  = $gallerys['gallery'];
    }
    
    if($gallerys){
        foreach($gallerys as $key => $gallery){
            $gallery = (array)$gallery;
        
            $id = $gallery['id'];
            $where = array('gid'=>$id);
            $gallery_contents = $db->db_select($table_gallery_content, $where);
        
            $gallery['default_pic'] = $base_url.'/uploads/gallery/'.$gallery['id'].'_'.$gallery['piyin'].'/default.jpg';
            $gallery['gallery_contents'] = $gallery_contents;
        
            $gallerys[$key] = $gallery;
        }        
    }

    return $gallerys;
}

/**
 * 获取目录信息, 如果有ID就获取指定目录信息，否则返回所有目录信息.
 */
function gallery_get_category($categoryid=NULL) {

  /* 1. 读取gallery.index */
  $categoryIndexes = file_handle_UFT8(file(GALLERY_CATEGORY_INDEX));

  foreach($categoryIndexes AS $categoryIndex) {
    $categorys[] = explode('|', $categoryIndex);
  }

  foreach($categorys AS $category){
    $categoryTrims = array();
    foreach($category AS $value){
      $categoryTrims[] = trim($value);
    }
    $categorysTrims[] = $categoryTrims;
  }

  if($categoryid){
    foreach($categorysTrims AS $categorysTrim) {
      if($categorysTrim[0] == $categoryid){
        return $categorysTrim;
      }
    }
  }

  return $categorys;
}

/**
 * 检查图册是否存在.
 */
function gallery_check_gid_exist($gid){

  if(!is_numeric($gid)) {
    return false;
  }

  if($gid <= 0){
    return false;
  }

  $gallery = gallery_load($gid);
  
  if($gallery){
      return true;
  }else{
      return false;
  }
  
}

/**
 * 根据图册名称检查是否存在
 */
function gallery_check_exist_new($name){
    //获取植物信息
    $db = new database;

    //表路径
    $table = DB_PATH.TABLE_GALLERY;

    //获取数据
    $where = array('name'=>$name);
    $plant = $db->db_select($table, $where);

    return $plant;
}

/**
 * 默认缩略图是否存在
 */
function gallery_check_default_thumb($path){

  $im = @imagecreatefromjpeg($path);

  if($im){
    return true;
  }else{
    return false;
  }

}

/**
 * 获取开始数字
 */
function gallery_get_start_number(){
  $sum = count(file_handle_UFT8(file(GALLERY_CATEGORY_INDEX)));
  $sum = $sum + 1;
  return $sum;
}

/**
 * 读取迁移内容
 */
function gallery_transfer_load(){
    $gallerys = array();
    
    //获取目录文件夹名字
    $categorys = gallery_get_category();
//     print_r($categorys);
    
    foreach($categorys as $key => $category){
      
        $categoryid             = trim($category[0]);
        $category_name          = trim($category[6]);
        $category_floder_name   = trim($category[0]).'_'.trim($category[5]);
        
        /* 1. 读取image.index */
        $imageIndex     = GALLERY_DATA_PATH.$category_floder_name.OS_SLASH.'image.index';
       
        $imageIndexes   = file_handle_UFT8(file($imageIndex));
        $nodes          = array();
        
        /* 2. 循环遍历 生成数组 $nodes_temp */
        foreach($imageIndexes AS $imageIndex) {
            if(strlen($imageIndex) > 5){
                $imageIndex = explode('|', $imageIndex);
                list($imageid, $name, $floder_name) = $imageIndex;
                $node = new stdClass();
                $node->nid = $imageid;
                $node->title = $name;
                $node->tid = $categoryid;
                $node->taxonomy = $category_name;
                $node->taxonomy_floder_name = $category_floder_name;
                $node->image_name = trim($floder_name).'.jpg';
                $node->image_thumb_name = trim($floder_name).'_thumb.jpg';
                $nodes[] = $node;
            }
        }     

        $categorys[$key]['images'] = $nodes;
    }

    return $categorys;    
}

/**
 * 迁移内容数据
 */
function gallery_transfer_content($gallerys){
    global $base_url;
    
    $db = new database;
    
    //表路径
    $table_gallery = DB_PATH.TABLE_GALLERY;
    $table_gallery_content = DB_PATH.TABLE_TAXONOMY_CONTENT_GALLERY;
    
    foreach($gallerys as $gallery){
    
        //获取数据
        $v = $db->db_select($table_gallery);
    
        //计算起始ID
        $attributes = (array)$v->attributes();
        if(is_array($attributes) && count($attributes)){
            foreach($attributes as $key => $value){
                $start_id = $value['start_id']+ 1;
            }
        }else{
            $start_id = 1;
        }
    
        $attributes = array('start_id'=>$start_id);
    
        //生成数据
        $data['gallery'] = array(
            'id'            => $start_id,
            'tid' 		    => trim($gallery[1]),
            'status' 		=> 1,
            'piyin' 	    => trim($gallery[2]),
            'created' 	    => trim($gallery[3]),
            'updated' 	    => trim($gallery[4]),
            'piyin'		    => trim($gallery[5]),
            'name' 		    => trim($gallery[6]),
            'keyword'	    => trim($gallery[7]),
            'description'   => trim($gallery[8]),
        );
    
        //写入gallery.xml
        $db->db_insert($table_gallery, $data, $attributes);
    
        //添加植物内容
        $gallery_images = $gallery['images'];
        //         print_r($gallery_images); die();
    
        foreach($gallery_images as $gallery_image){
            $v_content = $db->db_select($table_gallery_content);
    
            //计算起始ID
            $attributes_content = (array)$v_content->attributes();
            if(is_array($attributes_content) && count($attributes_content)){
                foreach($attributes_content as $key1 => $value1){
                    $start_id_content = $value1['start_id']+ 1;
                }
            }else{
                $start_id_content = 1;
            }
    
            $attributes = array('start_id'=>$start_id_content);
    
            //生成数据
            $taxonomy_gallery_content['gallery_content'] = array(                
                'id'			 			    => $start_id_content,
                'gid'						    => $start_id,
                'title' 						=> trim($gallery_image->title),
                'gallery_name' 					=> trim($gallery_image->taxonomy),
                'gallery_floder_name' 			=> trim($gallery_image->taxonomy_floder_name),
                'image_name' 	                => trim($gallery_image->image_name),
                'image_thumb_name'				=> trim($gallery_image->image_thumb_name),
            );
    
            //写入taxonomy_content_gallery.xml
            $db->db_insert($table_gallery_content, $taxonomy_gallery_content, $attributes);
        }
    }    
}

/**
 * 迁移图片
 */
function gallery_transfer_img($imgs){
    foreach($imgs as $key => $img){
        $images                 = $img['images'];
        $taxonomy_floder_name   = $images[0]->taxonomy_floder_name;
        
    
        $path = UPLOAD_PATH.OS_SLASH.'gallery';
        $floder_1 = $taxonomy_floder_name;
        $floder_2 = 'original';
        $floder_3 = 'thumb';
        $paths[0] = $path.OS_SLASH.$floder_1;       //主目录
        $paths[1] = $paths[0].OS_SLASH.$floder_2;   //原始图
        $paths[2] = $paths[0].OS_SLASH.$floder_3;   //缩略图
    
        if(!file_exists($paths[0])){
            file_create_folders($paths);
        }
    
        //原图
        if(@$images){
            foreach($images AS $image){
                $images_original        = $image->image_name;
                $images_thumb           = $image->image_thumb_name;
                
                $source_original_img = GALLERY_DATA_PATH.OS_SLASH.$taxonomy_floder_name.OS_SLASH.$images_original;
                $target_original_img = UPLOAD_PATH.OS_SLASH.'gallery'.OS_SLASH.$floder_1.OS_SLASH.'original'.OS_SLASH.$images_original;
                
                $source_thumb_img = GALLERY_DATA_PATH.OS_SLASH.$taxonomy_floder_name.OS_SLASH.$images_thumb;
                $target_thumb_img = UPLOAD_PATH.OS_SLASH.'gallery'.OS_SLASH.$floder_1.OS_SLASH.'thumb'.OS_SLASH.$images_thumb;
                    
                if (copy($source_original_img, $target_original_img)) {
                    echo "copy original successful - $source_original_img...<br>";
                }else{
                    echo "copy original failed - $source_original_img...<br>";
                }
                
                if (copy($source_thumb_img, $target_thumb_img)) {
                    echo "copy thumb successful -  $source_thumb_img...<br>";
                }else{
                    echo "copy thumb failed - $source_thumb_img...<br>";
                }
            }
        }
    
    
    }    
}

/**
 * 删除图片文件.
 */
function gallery_delete_pic(){
    $id        = $_REQUEST['id'];
    $gid        = $_REQUEST['gid'];
    $picname    = $_REQUEST['picname'];
    
    $gallery        = gallery_load($gid);
    $floder_name    = $gid.'_'.$gallery[0]['piyin'];
    
    $delete_path    = DOCUMENT_ROOT.OS_SLASH.'uploads'.OS_SLASH.'gallery'.OS_SLASH.$floder_name.OS_SLASH.'original'.OS_SLASH.$picname;
    $picname_1      = explode('.', $picname);
    $picname_1      = $picname_1[0].'_thumb.'.$picname_1[1];
    $delete_path_1  = DOCUMENT_ROOT.OS_SLASH.'uploads'.OS_SLASH.'gallery'.OS_SLASH.$floder_name.OS_SLASH.'thumb'.OS_SLASH.$picname_1;

    if(unlink($delete_path) && unlink($delete_path_1)){
        $table = DB_PATH.TABLE_TAXONOMY_CONTENT_GALLERY;
        $where = array('id'=>$id);
        $xpath = 'gallery_content';
        db_delete($table, $xpath, $where);

        header('Location: '.GALLERY_PHP_FILE.'?op=upload&gid='.$gid.'&message=删除图片成功!', TRUE, 302);
    }else{
        echo '删除 '.$delete_path.' - 失败!<br>';
    }

}

/**
 * 生成图册默认缩略图.
 */
function gallery_generate_thumbnail(){
  $gid = $_REQUEST['gid'];
  $picname = $_REQUEST['picname'];
  
  $gallery  = gallery_load($gid);
  
  $floder_name = $gid.'_'.$gallery[0]['piyin'];
  $thumbnail_name = 'default.jpg';

  $source_path = DOCUMENT_ROOT.OS_SLASH.'uploads'.OS_SLASH.'gallery'.OS_SLASH.$floder_name.OS_SLASH.'original'.OS_SLASH.$picname;

  $thumbnail_width = 190;
  $thumbnail_height = 200;
  $addition_name = THUMBNAIL_NAME;
  $type_name = ALLOW_IMAGE_TYPE;

  /*获取图片信息*/
  list($img_width, $img_height, $img_type, $img_attr) = getimagesize($source_path);
  /* 比例计算, 宽 > 高 或 宽 < 高 */
  if($img_width > $img_height){
    $narrow_percentage = round($thumbnail_width/$img_width, 2);
  }else{
    $narrow_percentage = round($thumbnail_height/$img_height, 2);
  }

  $narrow_width  = $img_width * $narrow_percentage;
  $narrow_height = $img_height * $narrow_percentage;

  // Resample
  $image_p = imagecreatetruecolor($narrow_width, $narrow_height);
  $image = imagecreatefromjpeg($source_path);

  imagecopyresampled($image_p, $image, 0, 0, 0, 0, $narrow_width, $narrow_height, $img_width, $img_height);
  ImageDestroy($image);

  /* 获取图片名称 */
  $target_store_path = DOCUMENT_ROOT.OS_SLASH.'uploads'.OS_SLASH.'gallery'.OS_SLASH.$floder_name.OS_SLASH.$thumbnail_name;

  /* 输出图片 */
  if(imagejpeg($image_p, $target_store_path, 100)){
    header('Location: '.GALLERY_PHP_FILE.'?op=upload&gid='.$gid.'&message=默认缩略图创建成功!', TRUE, 302);
  }else{
    echo $target_store_path.' - 默认缩略图创建失败!!! <br>';
  };


}

?>