package todo_server

import (
	"bytes"
	"fmt"
	"github.com/boltdb/bolt"
	"log"
)

var (
	err       error
	Data_base *bolt.DB
)

//======================================================================================================================
func PutDataDB(name_bucket, key, value []byte) error {

	put_error := Data_base.Update(func(tx *bolt.Tx) error {

		bucket, create_bucket_err := tx.CreateBucketIfNotExists(name_bucket)

		if create_bucket_err != nil {

			return create_bucket_err
		}

		put_value_err := bucket.Put(key, value)

		if put_value_err != nil {

			return put_value_err
		}

		return nil

	})

	return put_error
}

//======================================================================================================================
func GetDataDB(name_bucket, key []byte) []byte {

	var key_value []byte
	get_error := Data_base.View(func(tx *bolt.Tx) error {

		bucket := tx.Bucket(name_bucket)
		if bucket == nil {

			return fmt.Errorf("Bucket %q not found!", name_bucket)
		}
		key_value = bucket.Get(key)
		if key_value == nil {

			fmt.Printf("key %q not found", key)
		}
		return nil
	})
	CheckError(get_error)
	return key_value
}

//======================================================================================================================
func CheckUser(key string) bool {

	if GetDataDB([]byte("users"), []byte(key)) != nil {

		return true
	} else {

		return false
	}
}

//======================================================================================================================
func AddUser(key, value string) bool {

	if PutDataDB([]byte("users"), []byte(key), []byte(value)) == nil {

		return true
	} else {

		return false
	}
}

//======================================================================================================================
func AuthenticationUser(key, value string) bool {

	if key == "" || value == "" {

		return false
	}

	if bytes.Compare(GetDataDB([]byte("users"), []byte(key)), []byte(value)) == 0 {

		return true
	} else {

		return false
	}
}

//======================================================================================================================
func AddPost(key, value string) bool {

	if PutDataDB([]byte("posts"), []byte(key), []byte(value)) == nil {

		return true
	} else {

		return false
	}
}

//======================================================================================================================
func DeletePost(key string) bool {

	Data_base.Update(func(tx *bolt.Tx) error {

		name_bucket := tx.Bucket([]byte("posts"))
		name_bucket.Delete([]byte(key))
		return err
	})

	if err == nil {

		return true
	} else {

		log.Fatal(err)
		return false
	}
}

//======================================================================================================================
func GetAllPosts() map[string]string {

	post := make(map[string]string)
	Data_base.View(func(tx *bolt.Tx) error {

		name_bucket := tx.Bucket([]byte("posts"))

		name_bucket.ForEach(func(key, value []byte) error {

			post[string(key)] = string(value)
			return nil
		})
		return nil
	})
	return post
}

//======================================================================================================================
