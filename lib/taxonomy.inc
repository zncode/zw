<?php

function vocabulary_load($vid=NULL){
	$db = new database;
	//表路径
	$table = DB_PATH.TABLE_TAXONOMY_VOCABULARY;

	//获取数据
	if($vid){
		$where = array('vid'=>$vid);
		$v = $db->db_select($table, $where);
		return $v[0];
	}else{
		$v = $db->db_select($table);
		return $v;
	}

}

function taxonomy_vid_load($vid){
	$db = new database;
	//表路径
	$table = DB_PATH.TABLE_TAXONOMY_TERM_DATA;

	//获取数据
	$where = array('vid'=>$vid);
	$t = $db->db_select($table, $where);
	if($t){
		foreach($t AS $key => $value){
			$childs = array();
			$childs = taxonomy_hierarchy_load_childs($value['tid']);
			$parent = taxonomy_hierarchy_load_parent($value['tid']);

			if($childs){
				$t[$key]['childs'] = $childs;
			}else{
				$t[$key]['childs'] = 0;
			}
			$t[$key]['parent'] = $parent;

			//如果是子目录，不显示在顶级目录列表中.
			if($parent){
				unset($t[$key]);
			}
		}
	}


	return $t;
}

function taxonomy_tid_load($tid){
    $taxonomy = false;
    
	$db = new database;
	//表路径
	$table = DB_PATH.TABLE_TAXONOMY_TERM_DATA;

	//获取数据
	$where = array('tid'=>$tid);
	$t = $db->db_select($table, $where);
	if($t){
		foreach($t AS $key => $value){
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
		$taxonomy = $t[0];
	}
	return $taxonomy;
}

function taxonomy_hierarchy_save($tid, $parent){
	$is_update = false;

	$db = new database;

	//表路径
	$table = DB_PATH.TABLE_TAXONOMY_HIERARCHY;

	$xml  = simplexml_load_file($table);
	$xg   = $xml->xpath('relation');

	foreach($xg AS $key => $value){
		if($value->tid == $tid){
			$is_update = true;
			$value->parent = $parent;
			$xml->asXML($table);
		}
	}

	if(!$is_update){
		$is_child = taxonomy_hierarchy_check_is_child($tid);
		if(!$is_child){
			$childs = $xml->addChild('relation');
			$childs->addChild('tid', $tid);
			$childs->addChild('parent', $parent);
			$xml->asXML($table);
		}
	}

}

function taxonomy_hierarchy_load_childs($parent){
	$result = false;

	$db = new database;

	//表路径
	$table = DB_PATH.TABLE_TAXONOMY_HIERARCHY;

	$xml  = simplexml_load_file($table);

	foreach($xml->children() as $child) {
		if($child->parent == $parent){
			$tid = (array)$child->tid;
			$result[] = taxonomy_tid_load($tid[0]);
		}
	}

	return $result;
}

function taxonomy_hierarchy_load_parent($tid){
	$parent = 0;
	$db = new database;

	//表路径
	$table = DB_PATH.TABLE_TAXONOMY_HIERARCHY;

	$xml  = simplexml_load_file($table);

	foreach($xml->children() as $child) {
		if($child->tid == $tid){
			$parent = (array)$child->parent;
			$parent = $parent[0];
		}
	}

	return $parent;
}

function taxonomy_hierarchy_check_is_child($tid){
	$is_child = false;

	$db = new database;

	//表路径
	$table = DB_PATH.TABLE_TAXONOMY_HIERARCHY;
	$xml  = simplexml_load_file($table);
	$xg   = $xml->xpath('relation');

	foreach($xg AS $key => $value){
		if($value->tid == $tid && $value->parent != 0){
			$is_child = true;
		}
	}

	return $is_child;
}
?>