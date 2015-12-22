<?php

$page_clear = page_clear();
define('PLANT_PAGER_LIMIT', 18);
define('PLANT_BASE_PATH', 'plant');

/**
 * 植物页面
 */

class PagePlant extends Page{

  /**
   * 显示类型
   */
  public $plant_displaytype = 'overview';

  /**
   * 植物ID
   */
  public $plantID = false;

  /**
   * 植物内容
   */
  public $plant_content = '';

  /**
   * 植物内容ID
   */
  public $plant_content_id = false;

  /**
   * 植物信息
   */
  public $plants;

  /**
   * 植物分类信息
   */
  public $plant_category;

  /**
   * 是否显示植物总览页面
   */
  public $is_overiew = false;

  /**
   * 是否显示植物详细页面
   */
  public $is_detail = false;

  /**
   * 所选植物是否包含在多个目录中
   */
  public $more_category = false;

  /**
   * 设置植物显示类型
   */
  public function SetPlantDisplayType($value){
    $this->plant_displaytype = $value;
  }

  /**
   * 设置植物信息
   */
  public function SetPlantID($value){
    $this->plantID = $value;
  }

  /**
   * 设置植物信息
   */
  public function SetPlantContentID($value){
      $this->plant_content_id = $value;
  }

  /**
   * 设置植物信息
   */
  public function SetPlants($value){
    $this->plants = $value;
  }

  /**
   * 设置植物信息
   */
  public function SetPlantContent($value){
      $this->plant_content = $value;
  }

  /**
   * 设置植物分类信息
   */
  public function SetPlantCategory($value){
    $this->plant_category = $value;
  }

  /**
   * 设置导航条
   */
  public function SetBreadcrumb($breadcreambs=false){
    $breadcrumbNews = $this->breadcrumbs;
    if(is_array($breadcreambs) && count($breadcreambs)){
      foreach($breadcreambs AS $breadcreamb){
        foreach($breadcreamb AS $path => $title){
          if($path != 'title'){
            $breadcrumbNews[] = l(t($title), $path);
          }else{
            $breadcrumbNews[] = $title;
          }
        }
      }
    }
    $this->breadcrumbs = $breadcrumbNews;
  }

  /**
   * 设置是否包含多目录
   */
  public function SetMoreCategory($value){
    $this->more_category = $value;
  }

  /**
   * 显示页面内容
   */
  public function DisplayContent(){
    $displayType = $this->plant_displaytype;
    switch($displayType){
      case 'overview':
        echo '<div class="plant_overview_wrapper">';
        $this->DisplayBreadcrumb();
        $this->DisplayOverview();
        echo '</div>';
        break;
      case 'detail':
        echo '<div class="plant_detail_wrapper">';
        $this->DisplayBreadcrumb();
        $this->DisplayDetail();
        echo '</div>';
    }
  }

  /**
   * 显示总览页面
   */
  public function DisplayOverview(){
    global $base_url, $page_clear;

    $plants = $this->plants;
    $taxonomy = $this->taxonomy;

      $output = '<div class="content">';
        $output .= '<ul>';
        if($plants){
          foreach($plants AS $cid => $plant){
            $link_url    = PLANT_BASE_PATH.'/'.$cid;
            $path        = $plant[0]['images']['thumbnail'];
            $image_thumb = l('<img src="'.$path.'" alt="'.$plant[0]['name'].'" />', $link_url).'<br>';

            $output .= '<li> '.$image_thumb.l($plant[0]['name'], $link_url).' </li>';
          }
        }else {
          $output .= '<li> 暂时无内容 <li>';
        }

        $output .= '</ul>';
      $output .= '</div>';

      $output .= $page_clear;
      // add pager
      if($this->pager) {
        $output .= $this->pager;
      }

    echo $output;
  }

  /**
   * 显示详细页面
   */
  public function DisplayDetail(){
    global $base_url,$page_clear;

    $output = '';

    $plant = $this->plants;
    $plant_content = $this->plant_content;

      /* content */
      $output ='<div class="content">';
        $output .='<div class="tree_content_wrapper">';
        if($plant_content){
          $name = $plant['name'];
          $content = html_content($plant_content['content']);

          $output .='<div class="title"><h1>'.$name.'</h1></div>';
          $output .='<div class="text">';
          $output .= $content;
          $output .= '</div>';

        }else {
          $output .= '<div class="text"> 暂无内容 </div>';
        }
      $output .= '</div>';

      /* photo gallery */
      $output .='<div class="tree_gallery_wrapper">';
        $images             = $plant['images'];
        $images_thumbs      = $images['thumbs'];
        $images_originals   = $images['originals'];

        $output .= '<ul>';
        if(is_array($images_thumbs) && count($images_thumbs)) {

          foreach($images_thumbs AS $key => $images_thumb){
            $output .= '<li>';
            $output .= '<a href="'.$images_originals[$key].'" target="_blank"><img src="'.$images_thumb.'" alt="'.$name.'" /></a>';
            $output .= '</li>';
          }
        }else{
          $output .= '暂无图片';
        }
        $output .= '</ul>';
      $output .= '</div>';
      $output .= $page_clear;

    //百度文章页广告
    $output .= '<div class="ad_plant_bottom"><script type="text/javascript">var cpro_id = "u1588384";</script><script src="http://cpro.baidustatic.com/cpro/ui/c.js" type="text/javascript"></script></div>';

    echo $output;
  }

  /**
   * 显示页面
   */
  public function DisplayPage(){
    echo '<!DOCTYPE html><html lang="zh">';
    echo '<head>';
    $this->DisplayTitle();
    $this->DisplayMeta();
    $this->DisplayStyles();
    echo '</head>';
    echo '<body>';
      if($this->pagenotfound){
        $this->DisplayPageNotFound();
      }else{
        $this->DisplayHeader();
        $this->DisplayContent();
        $this->DisplayPageClear();
        $this->DisplayFooter();
      }

    echo '</body>';
    echo '</html>';
  }
}

/**
 * 显示植物页面内容
 */
function plant_display_content($arg){
    global $page_title;
    $pagenotfound = false;

    switch($arg[0]){
        case 'plant':
            $cid            = $arg[1];
            $plant_content  = plant_content_load($cid);
            $plant_content  = $plant_content[0];
            if($plant_content){
                $plant_displaytype  = 'detail';
                $pager              = false;
                $plant              = plant_load_new($plant_content['pid']);
                $plant              = $plant[0];

                $pid                = $plant_content['pid'];
                $tid                = $plant_content['tid'];
                $plant_name         = $plant['name'];
                $meta_keywords      = $plant_content['meta_keyword'];
                $meta_description   = $plant_content['meta_description'];

                $taxonomy           = taxonomy_tid_load($tid);
                $taxonomy_name      = $taxonomy['name'];

                $pagetitle          = $plant_name.'_'.$taxonomy_name.'_'.$page_title;

                if($taxonomy['parent']){
                    $breadcrumbs[] = array('plant_category/'.$taxonomy['parent']['tid'] => $taxonomy['parent']['name']);
                }
                $breadcrumbs[] = array('plant_category/'.$taxonomy['tid'] => $taxonomy_name);
                $breadcrumbs[] = array('title' => $plant_name);
            }else{
                $pagenotfound = true;
            }

            break;

        case 'plant_category':
            $plant_displaytype  = 'overview';
            $tid                = $arg[1];
            $taxonomy           = taxonomy_tid_load($tid);

            if($taxonomy){
                $pagetitle          = $taxonomy['name'].'_'.$page_title;

                $taxonomy_name      = $taxonomy['name'];
                $meta_keywords      = $taxonomy['keyword'];
                $meta_description   = $taxonomy['description'];

                $pagers = plant_pager_load($tid);
                $plants = $pagers['pager_content'];
                krsort($plants);
                $pager  = $pagers['pager_html'];

                $breadcrumbs[] = array('title'=>$taxonomy_name);

            }else{
                $pagenotfound = true;
            }
            break;
    }

    $page = new PagePlant();

    if($pagenotfound){
        $page->SetPagenotfound($pagenotfound);
        $page->SetTitle('页面没有找到');
    }else{
        if($plant_displaytype == 'detail'){
            $page->SetPlantDisplayType($plant_displaytype);
            $page->SetTitle($pagetitle);
            $page->SetMetaKeywords($meta_keywords);
            $page->SetMetaDescription($meta_description);
            $page->SetPlantContent($plant_content);
            $page->SetPlants($plant);
            $page->SetBreadcrumb($breadcrumbs);
            $page->SetPager($pager);
        }else{
            $page->SetPlantDisplayType($plant_displaytype);
            $page->SetTitle($pagetitle);
            $page->SetMetaKeywords($meta_keywords);
            $page->SetMetaDescription($meta_description);
            $page->SetPlants($plants);
            $page->SetBreadcrumb($breadcrumbs);
            $page->SetPager($pager);
            $page->SetTaxonomy($taxonomy);

        }

    }

    $page->DisplayPage();
}



function plant_pager_load($tid){
    $pagers         = array();
    $plant_pagers   = false;
    $pager_html     = false;
    $pager_limit    = PLANT_PAGER_LIMIT;
    $pager_id       = 1;

    if(@$_REQUEST['pager']){
        $pager_id = $_REQUEST['pager'];
    }

    /* 计算起始位置 */
    if($pager_id == 1){
        $start = 0;
        $end = $pager_limit - 1;
    }elseif($pager_id == 2) {
        $start = $pager_limit;
        $end = $start+$pager_limit-1;
    }else{
        $start = $pager_limit*($pager_id-1);
        $end = $start+$pager_limit-1;
    }

    $page_count = 0;

    //读取内容
    $plants = plant_load_by_tid($tid);

    foreach($plants as $cid => $plant){
        if($end >= $page_count && $page_count >= $start){
           $plant_pagers[$cid] = $plant;
        }

        /* 对应目录下 记数增加 */
        $page_count++;
    }

    $count = count($plants);

    $pager_html = plant_pager_html($pager_id, $count);

    $pagers['pager_html']       = $pager_html;
    $pagers['pager_content']    = $plant_pagers;

    return $pagers;
}


function plant_pager_html($pager_id, $count){
//     $pager_id = 1;

//     if(@$_REQUEST['pager']){
//         $pager_id = $_REQUEST['pager'];
//     }
    $pager_html = false;
    $pager_limit = PLANT_PAGER_LIMIT;

    //读取内容
//     $plants = plant_load_by_tid($tid);

//     $count=count($plants);

    /* 获取当前路径 */
    $arg = arg();
    if($arg[0] == 'front' || empty($arg[0])){
        $current_path = NULL;
    }else{
        $current_path = implode('/', $arg);
    }
    /* 计算 */
    if($count) {
        /* How many pages */
        $pages = ceil($count / $pager_limit);
        if($pages > 1) {
            $pages = $pages + 1;
            /* Generate HTML pager */
            $pager_html = '<div class="pager">';
            $pager_html .= '<ul>';

            for($i=1; $i < $pages; $i++){
                if($i == 1 && $i == $pager_id){
                    $pager_html .= '<li class="page_current">'.$i.'</li>';

                }else {
                    if($i == $pager_id){
                        $pager_html .= '<li class="page_current">'.l($i, $current_path.'?pager='.$i).'</li>';
                    }else{
                        $pager_html .= '<li>'.l($i, $current_path.'&pager='.$i).'</li>';
                    }
                }
            }
            $pager_html .= '</ul>';
            $pager_html .= '</div>';
        }else {
            return false;
        }
    }
    return $pager_html;
}

/**
 * 读取单个植物
 */
function plant_load_all(){
    $db = new database;

    $plants = false;

    //表路径
    $table = DB_PATH.TABLE_PLANT;
    $xml  = simplexml_load_file($table);
    $plants = $xml->xpath("plant");


    return  $plants;
}

/**
 * 读取单个植物
 */
function plant_load_new($pid=NULL){
    global $base_url;


    //获取植物信息
    $db = new database;

    //表路径
    $table = DB_PATH.TABLE_PLANT;
    // 	$table_content = DB_PATH.TABLE_TAXONOMY_CONTENT_PLANT;

    //获取数据
    $where = array('pid'=>$pid);
    $plant = $db->db_select($table, $where);

    //获取内容
    // 	$plant_content = $db->db_select($table_content, $where);
    // 	$plant[0]['contents'] = $plant_content;

    if(!$plant){
        return false;
    }

    //获取上传图片
    $piyin = $plant[0]['piyin'];
    $path = UPLOAD_PATH.OS_SLASH.'plant';

    $floder_1 = $pid.'_'.$piyin;
    $floder_2 = 'default';
    $floder_3 = 'original';
    $floder_4 = 'thumb';
    $paths[0] = $path.OS_SLASH.$floder_1;       //主目录
    $paths[1] = $paths[0].OS_SLASH.$floder_2;   //默认分类
    $paths[2] = $paths[1].OS_SLASH.$floder_3;   //原始图
    $paths[3] = $paths[1].OS_SLASH.$floder_4;   //缩略图

    $originals = file_get_folder_names($paths[2]);
    $thumbs    = file_get_folder_names($paths[3]);

    $original_path  = $base_url.'/uploads/plant/'.$floder_1.'/default/original/';
    $thumb_path     = $base_url.'/uploads/plant/'.$floder_1.'/default/thumb/';
    $thumbnail_path = $base_url.'/uploads/plant/'.$floder_1.'/default/';

    if(count($originals)){
        foreach ($originals as $originals_value){
            $originals_new[] = $original_path.$originals_value;

        }
    }else{
        $originals_new = '';
    }

    if(count($thumbs)){
        foreach ($thumbs as $thumbs_value){
            $thumbs_new[] = $thumb_path.$thumbs_value;
        }
    }else{
        $originals_new = '';
    }

    $plant[0]['images']['originals']   = $originals_new;
    $plant[0]['images']['thumbs']      = $thumbs_new;
	  $plant[0]['images']['originals_name'] = $originals;
    $plant[0]['images']['thumbs_name']    = $thumbs;

    if(file_exists($paths[1].OS_SLASH.$piyin.'.jpg')){
        $plant[0]['images']['thumbnail']   = $thumbnail_path.$piyin.'.jpg';
    }else{
        $plant[0]['images']['thumbnail']   = NULL;
    }

    return $plant;
}

/**
 * 读取植物根据taxonomy id
 */
function plant_load_by_tid($tid){
    $result = false;

    $db = new database;

    //表路径
    $table = DB_PATH.TABLE_TAXONOMY_CONTENT_PLANT;

    //获取数据
    $where = array('tid'=>$tid);
    $plants = $db->db_select($table, $where);
    if($plants){
        foreach($plants as $key => $plant){
            $cid = $plant['cid'];
            $pids[$cid] = $plant['pid'];
        }

        foreach($pids as $cid => $pid){
            $result[$cid] = plant_load_new($pid);
        }
    }

    return $result;
}

function plant_load_by_name($name){
	$db = new database;
	//表路径
	$table = DB_PATH.TABLE_PLANT;

	//获取数据
	$where = array('name'=>$name);
	$plant = $db->db_select($table, $where);
	if($plant){
		foreach($plant AS $key => $value){
			$childs = array();
			$childs = taxonomy_hierarchy_load_childs($value['tid']);
			$parent = taxonomy_hierarchy_load_parent($value['tid']);

			if($childs){
				$t[$key]['childs'] = $childs;
			}else{
				$t[$key]['childs'] = 0;
			}
			$t[$key]['parent'] = $parent;

		}
	}else{
		return false;
	}
	return $t[0];
}

/**
 * 读取植物所属的所有内容
 */
function plant_load_content($pid=NULL){

    //获取植物信息
    $db = new database;

    //表路径
    $table = DB_PATH.TABLE_TAXONOMY_CONTENT_PLANT;

    //获取数据
    $where = array('pid'=>$pid);
    $plant = $db->db_select($table, $where);

    return $plant;
}

/**
 * 读取单个植物
 */
function plant_content_load($cid=NULL){

	//获取植物信息
	$db = new database;

	//表路径
	$table = DB_PATH.TABLE_TAXONOMY_CONTENT_PLANT;

	//获取数据
	$where = array('cid'=>$cid);
	$plant = $db->db_select($table, $where);

	return $plant;
}

/**
 * 获取给定分类下植物总数.
 */
function plant_count_by_tid($tid){
    $count = 0;

    $db = new database;
    //表路径
    $table = DB_PATH.TABLE_TAXONOMY_PLANT;

    //获取数据
    $where = array('tid'=>$tid);
    $plant = $db->db_select($table, $where);
    if($plant){
        $count = count($plant);
    }

    return $count;
}

/**
 * 根据植物名称检查Plant是否存在
 */
function plant_check_exist_new($name){
	//获取植物信息
	$db = new database;

	//表路径
	$table = DB_PATH.TABLE_PLANT;

	//获取数据
	$where = array('name'=>$name);
	$plant = $db->db_select($table, $where);

  return $plant;
}


?>