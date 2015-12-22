<?php
//路径
define('DB_PATH',		DOCUMENT_ROOT.OS_SLASH.'db'.OS_SLASH.'table'.OS_SLASH);
define('DB_PATH_PLANT',	DOCUMENT_ROOT.OS_SLASH.'db'.OS_SLASH.'plant'.OS_SLASH);


//数据库表名
define('TABLE_TAXONOMY_VOCABULARY', 	'taxonomy_vocabulary.xml');
define('TABLE_TAXONOMY_TERM_DATA', 		'taxonomy_term_data.xml');
define('TABLE_TAXONOMY_HIERARCHY', 		'taxonomy_hierarchy.xml');
define('TABLE_TAXONOMY_CONTENT_PLANT', 			'taxonomy_content_plant.xml');
define('TABLE_TAXONOMY_CONTENT_ARTICLE', 		'taxonomy_content_article.xml');
define('TABLE_TAXONOMY_CONTENT_GALLERY', 		'taxonomy_content_gallery.xml');
define('TABLE_PLANT', 					'plant.xml');
define('TABLE_ARTICLE', 				'article.xml');
define('TABLE_GALLERY', 				'gallery.xml');


class database {

	public function db_select($table, $where=array()){
	    $result = NULL;
		$xml  = simplexml_load_file($table);
		
		if(is_array($where) && count($where)){
	        foreach($xml->children() as $child) {
	            
	            foreach($where as $key => $value){
	                if($child->$key == $value){
	                    $result[] = (array)$child;
	                }
	            }
	        }
	    }else{
	        $result = $xml;
	    }	
	    
		return $result;
	}

	/**
	 * 支持二维数组写入xml，如果是二维数组需要加id属性。
	 */
	public function db_insert($table, $data, $attributes=NULL){
		$xml = simplexml_load_file($table);
		if($attributes){
			foreach($attributes as $key => $value){
				if($xml->attributes()->$key){
					$xml->attributes()->$key = $value;
				}else{
					$xml->addattribute('start_id', 1);
				}
			}
		}
		foreach($data AS $key => $value){
			if(is_array($value)){
				$childs = $xml->addChild($key);
				foreach($value AS $key1 => $value1){
					$childs->addChild($key1, $value1);
				}
			}else{
				$xml->addChild($key, $value);
			}

		}
  		$xml->asXML($table);
	}

	public function db_update($table, $xpath, $where, $data){
		$xml = simplexml_load_file($table);

		$xg=$xml->xpath("$xpath");

		foreach($xg AS $key => $value){
			foreach($where as $key1 => $value1){
				if($value->$key1 == $value1){
					foreach($data AS $key2 => $value2){
						$value->$key2 = $value2;
					}
				}
			}
		}

		$xml->asXML($table);
	}
	
	public function db_delete($table, $xpath, $where){
	    $xml = simplexml_load_file($table);
	      
	    $xg=$xml->xpath("$xpath");
	    foreach($xg AS $key => $value){
	        foreach($where as $key1 => $value1){
	           
	            if($value->$key1 == $value1){
	                unset($xml->gallery_content[$key]);
	            }
	        }
	    }

	    $xml->asXML($table);
	}	
}

function db_insert($table, $data){
    $db = new database;
    
    //获取数据
    $v = $db->db_select($table);
    
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
    
    foreach($data as $key => $value){
        $data[$key]['id'] = $start_id;
    }
    
    //写入plant.xml
    $db->db_insert($table, $data, $attributes);    
}

function db_delete($table, $xpath, $where){
    $db = new database;

    //获取数据
    $v = $db->db_delete($table, $xpath, $where);
}

?>