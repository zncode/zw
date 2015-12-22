<?php 

/**
 * 上传函数
 * @param 源文件               $original_file
 * @param 上传路径           $upload_path
 * @param 文件大小限制    $size_limit
 */
function zw_upload($upload_path, $width_limit=1024, $size_limit=3000000){
    if(count($_FILES)) {
        $upload_file = $_FILES;
        
        $file_type      = $upload_file['filename']['type'];
        $file_old_name  = $upload_file['filename']['name'];
        $file_tmp_name  = $upload_file['filename']['tmp_name'];
        $file_error     = $upload_file['filename']['error'];
        $file_size      = $upload_file['filename']['size'];
        
        if($file_size > $size_limit) {
            echo 'Error: Upload file is too big false!!!!! (3MB max)';
            return false;
        }
        
        if($file_type == 'image/jpeg'){
            $file_old_name_array = explode(".", $file_old_name);
            $extend_filename = '.'.end($file_old_name_array);
        }else{
            echo 'Error: Upload file type false!!!!! (only jpg)';
            return false;
        }
        
        /* 裁剪图片  width > 1024 */
        image_max_resize($file_tmp_name, $width_limit);

        if(move_uploaded_file($file_tmp_name, $upload_path)) {
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}
?>