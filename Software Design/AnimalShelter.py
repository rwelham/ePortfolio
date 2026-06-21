from pymongo import MongoClient
from bson.objectid import ObjectId

class AnimalShelter(object):
  
  def __init__(self):
    #
    # Connection Variables
    #
    USER = 'aacuser'
    PASS = 92050
    HOST = 'nv-desktop-services.apporto.com'
    PORT = 32744
    DB = 'AAC'
    COL = 'animals'
    #
    # Initialize Connection 
    #
    self.client = MongoClient('mongodb://%s:%s@%s:%d' % (USER, PASS, HOST, PORT))
    self.database = self.client['%s' %  (DB)]
    self.collection = self.database['%s' % (COL)]
    
  # test database connection 
  def con_test(self):
    out = self.database.animals.find_one()
    return out
  
  # create method
  def create(self, data):
    if data is not None:
      #data should be a list of dictionaries
      #allows for multiple dictionaries to be added
      for i in data:
        # i is a dictionary
        # use getNextRecordNum() to find the next
        # recordnum should be and replace it prior to inserting
        index_num = self.getNextRecordNum()
        
        # Debug statements
        ## print ("Testing in Create")
        ## print(index_num)
        
        #update record number
        i.update({"rec_num":index_num})
        
        #remove id field
        i.pop("_id", None)
        
        # Debug statements to check i
        ## print(i)
        
        ret = self.database.animals.insert_one(i)
        
        # Debug statements to check ret
        ## print(ret.inserted_id)
        
        # check that it is a valid objectId
        if ret.inserted_id.is_valid(ret.inserted_id):
          #ObjectId is valid
          continue
        else: 
          return False
    else: 
      raise Exception("Nothing to save, because data parameter is empty")
      return False
    return True
        
  # read method
  def read(self, data):
    # data should be a partial dictionary to search the records
    if data is not None:
      #returned cursor can be used to become a list
      cursor = self.database.animals.find(data, {"_id": False})
      out = []
      for doc in cursor:
        out.append(doc)
        # Debug commands for testing
        ## numRec = len(out)
        ## print ("Returning %d records" % (numRec))
    else:
      out = self.database.animals.find_one()
    return out

  # update method
  def update(self, query, data):
    if query and data is not None:
      updated = self.database.animals.update_many(query, {"$set": data})
    else:
      raise Exception("Nothing to update, query or data parameters are empty")
    return update.modified_count
  
  # delete method
  def delete(self, data):
    if data is not None:
      deleted = self.database.animals.delete_many(data)
    else: 
      raise Exception("Nothing to delete, data parameter is empty")
    return deleted.deleted_count
  
