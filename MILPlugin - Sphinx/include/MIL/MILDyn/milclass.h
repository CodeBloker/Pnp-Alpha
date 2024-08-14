////////////////////////////////////////////////////////////////////////////////
//! 
//! \brief Milclass CAPI header (Mclass...)
//! 
//! AUTHOR: Matrox Imaging
//!
//! COPYRIGHT NOTICE:
//! Copyright (c) Matrox Electronic Systems Ltd., 1992-2021.
//! All Rights Reserved 
//  Revision:  10.40.0881
////////////////////////////////////////////////////////////////////////////////

#ifndef __MIL_CLASS_H__
#define __MIL_CLASS_H__

#if (!M_MIL_LITE) /* MIL FULL ONLY */

#if M_MIL_USE_RT
#ifdef M_CLASS_EXPORTS
#define MIL_CLASS_DLLFUNC __declspec(dllexport)
#else
#define MIL_CLASS_DLLFUNC __declspec(dllimport)
#endif
#else
#define MIL_CLASS_DLLFUNC
#endif

#define M_MIL_SUPPORT_CLASS_CNN_TRAINING    (M_MIL_USE_WINDOWS && M_MIL_USE_64BIT)

// A Dataset entry key is a MIL_UUID
#define M_COMPARE_MIL_KEY(A, B)  M_COMPARE_MIL_UUID((A), (B))
#define M_IS_DEFAULT_KEY(A)      M_IS_DEFAULT_UUID((A))
#define M_IS_NULL_KEY(A)         M_IS_NULL_UUID((A))
#define M_DEFAULT_KEY            M_DEFAULT_UUID
#define M_NULL_KEY               M_NULL_UUID

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
   {
#endif

 typedef MIL_INT(MFTYPE *MIL_CLASS_HOOK_FUNCTION_PTR)(MIL_INT HookType,
                                                      MIL_ID  EventId,
                                                      void    *UserDataPtr);


////////////////////////////////////////////////////////////////////////////////
// MclassAlloc ContextTypes

#define M_CLASSIFIER_CNN                              2779L           
#define M_CLASSIFIER_CNN_PREDEFINED                   2913L

#if OldDefinesSupport
#define M_CONVOLUTIONAL_NETWORK                       M_CLASSIFIER_CNN
#define M_PREDEFINED_CONVOLUTIONAL_NETWORK            M_CLASSIFIER_CNN_PREDEFINED
MIL_DEPRECATED(M_CONVOLUTIONAL_NETWORK, 1040)                         
MIL_DEPRECATED(M_PREDEFINED_CONVOLUTIONAL_NETWORK, 1040)
#endif

#define M_PREDICT_CNN_RESULT                          3754L

#define M_TRAIN_CNN                                   4213L
#define M_TRAIN_CNN_RESULT                            3755L

#define M_CLASSIFIER_TREE_ENSEMBLE                    3265L
#define M_PREDICT_TREE_ENSEMBLE_RESULT                3756L 
#define M_TRAIN_TREE_ENSEMBLE                         3521L 
#define M_TRAIN_TREE_ENSEMBLE_RESULT                  3757L 

#define M_DATASET_IMAGES                              3473L
#define M_DATASET_FEATURES                            3946L

// MclassAlloc ControlFlags
#define M_FCNET_S                                     0x20000001L
#define M_FCNET_M                                     0x20000002L
#define M_FCNET_XL                                    0x20000003L
#define M_FCNET_MONO_XL                               0x20000004L
#define M_FCNET_COLOR_XL                              0x20000005L

// Classifier predefined type
#define M_USER_ONNX                                   4761L

// Dataset Control/Inquire types
#define M_DATASET                                     3802L
#define M_ENTRIES                                     3571L
#define M_AUTHORS                                     3769L
#define M_CLASS_DEFINITIONS                           3476L

#define M_ENTRY_ADD                                   3474L
#define M_ENTRY_DELETE                                3477L
#define M_ENTRY_DELETE_BY_KEY                         3573L
#define M_ENTRY_DELETE_ALL                            3784L
#define M_ENTRY_INDEX                                 3653L
#define M_ENTRY_KEY                                   3575L

#define M_FORMAT_CSV                                  3572L
#define M_FORMAT_TXT                                  3945L
#define M_ENTRY_USER_STRING                           (3649L | M_CLIENT_ENCODING)

#define M_NUMBER_OF_REGIONS                           3652L
#define M_REGION_TYPE                                 1058L // also in mil.h
#define M_WHOLE_IMAGE                                    1L // also in milblob.h

#define M_CLASS_ADD                                   3740L
#define M_CLASS_DELETE                                3741L
#define M_CLASS_DELETE_BY_KEY                         3742L
#define M_CLASS_INDEX_GROUND_TRUTH                    3478L 
#define M_CLASS_INDEX_PREDICTED                       3738L 
#define M_ENTRY_WEIGHT                                3576L 
#define M_PREDICTED_CLASS_SCORES                      3739L

#define M_FILE_PATH                                   (3475L | M_CLIENT_ENCODING)
#define M_FILE_PATH_ABS                               (3743L | M_CLIENT_ENCODING)
#define M_ROOT_PATH                                   (3744L | M_CLIENT_ENCODING)
#define M_MAKE_FILE_PATHS_RELATIVE                    3749L 
#define M_MAKE_FILE_PATHS_ABSOLUTE                    3750L 

#define M_SORT                                  0x00200000L // already defined

#define M_RAW_DATA                              0x00000094L // already defined in milcode.h

#define M_AUGMENTATION_SOURCE                         3841L
#define M_AUGMENTATION_SOURCE_KEY                     3842L

#define M_USER_CONFIDENCE                             4013L

#define M_AUTHOR_ADD                                  3770L
#define M_AUTHOR_DELETE                               3771L
#define M_AUTHOR_DELETE_BY_KEY                        3772L
#define M_NUMBER_OF_AUTHORS                           3773L
#define M_AUTHOR_KEY                                  3774L
#define M_AUTHOR_NAME                                 (3655L | M_CLIENT_ENCODING)
#define M_ACTIVE_AUTHOR_INDEX                         3777L
#define M_CURRENT_USER_U79                            3778L
#define M_CURRENT_USER_PP4                      0x00010000L
#define M_CURRENT_USER                   M_CURRENT_USER_PP4
#define M_ACTIVE_AUTHOR_UPDATE                        3924L



#define M_UNKNOWN_UUID                       M_DEFAULT_UUID
#define M_UNKNOWN_KEY                        M_UNKNOWN_UUID
#define M_NOT_AUGMENTED                                 -1L 
#define M_UNKNOWN                                    -9999L // already defined in mil.h, milpat.h

////////////////////////////////////////////////////////////////////////////////   
// Indexing, used in other Mclass functions (MclassInquire(), MclassControl(), ...)
#define M_DEFAULT                               0x10000000L // already defined
#define M_CONTEXT                               0x08000000L // already defined
#define M_GENERAL                               0x20000000L // already defined
#define M_ALL                                   0x40000000L // already defined
#define M_ANY                                   0x11000000L // already defined

// Control and result types modifiers, also used in MclassCopyResult
#define M_AVAILABLE                             MAKE_INT64(0x0000400000000000) // also defined in mil.h
#define M_SUPPORTED                             MAKE_INT64(0x0000800000000000) // also defined in mil.h


#define M_CLASS_NAME                                 (3297L | M_CLIENT_ENCODING)
#define M_CLASS_DEF_UUID                             (3298L | M_CLIENT_ENCODING)
#define M_CLASS_DRAW_COLOR                            3319L
#define M_CLASS_KEY                                   3574L 


#define M_OWNER_SYSTEM                                1101L // already defined
#define M_MODIFICATION_COUNT                          5010L // already defined

#define M_MAX_POSSIBLE_LABEL_VALUE              ((~(0xFFE00000L)) & 0xFFFFFFFFL)              
#define M_MAX_POSSIBLE_INDEX_VALUE              M_MAX_POSSIBLE_LABEL_VALUE                    



#define M_DEFAULT_SOURCE_LAYER                  0x02100000L
#define M_DEFAULT_NO_LAYER                      0x02040000L

#define M_CLASS_DEF_INDEX_FLAG                  0x00200000L

#define M_REGION_INDEX_FLAG                     0x01000000L
#define M_AUTHOR_INDEX_FLAG                     0x04000000L




#define M_CLASS_DESCRIPTION(IndexValue) (M_CLASS_DEF_INDEX_FLAG | (IndexValue))
#define M_CLASS_INDEX(IndexValue)       (M_CLASS_DEF_INDEX_FLAG | (IndexValue))

#define M_REGION_INDEX(IndexValue)      (M_REGION_INDEX_FLAG | (IndexValue))

#define M_AUTHOR_INDEX(IndexValue)      (M_AUTHOR_INDEX_FLAG | (IndexValue))



#define M_TIMEOUT                                     2077L // already defined

#define M_SOURCE                                      2800L
#define M_OUTPUT                                         3L // already defined in mil.h

////////////////////////////////////////////////////////////////////////////////
// MclassControl

#define M_TIMEOUT                                     2077L // already defined

////////////////////////////////////////////////////////////////////////////////
// MclassControl / MclassInquire
// Context 

#define M_ENABLE                                     -9997L // already defined
#define M_DISABLE                                    -9999L // already defined

#define M_AUTO                                         444L // already defined
#define M_USER_DEFINED                                  21L // already defined

#define M_STOP_PREDICT                                2785L
#define M_STOP_TRAIN                                  2698L // also in milcode.h

#define M_PREPROCESSED                                  14L // already defined




#define M_RESET_TRAINING_VALUES                       3719L
#define M_LATEST_USED_RESET_TRAINING_VALUES           3954L


#define M_SIZE                                       0xC00L // already defined
#define M_SIZE_X                                      1536L // already defined
#define M_SIZE_Y                                      1537L // already defined
#define M_STEP_X                                      3971L 
#define M_STEP_Y                                      3972L 
#define M_SIZE_BAND                                   1005L // already defined
#define M_BAND_ORDER                                  3036L

#define M_RGB                                            8L // already defined in mil.h, milcolor.h
#define M_BGR                                         0x07L

#define M_METHOD                                       103L // already defined

#define M_MAX                                   0x04000000L // already defined
#define M_AVERAGE                               0x00000020L // already defined



#define M_OVERSCAN                                      53L // already defined



#define M_TYPE                                        1008L // already defined
#define M_GLOBAL                                0x00000008L // already defined
#define M_LOCAL                                 0x01000000  // already defined


#define M_IDENTITY                                       6L // already defined

#define M_DECAY                                       3486L
#define M_CYCLICAL_DECAY                              3491L

#define M_ALWAYS                                         0L // already defined in Milblob.h
#define M_ONCE                                           3L // already defined in mil.h


#define M_SUPPORT_MISSING_GROUND_TRUTH                3950L



#define M_HOST                                         100L // already defined

#define M_EXPIRY_DATE_STRING                          (2990L | M_CLIENT_ENCODING)

#define M_GAMMA                                       6672L // already defined
#define M_MEAN                                  0x08000000L // already defined
#define M_VARIANCE                              0x01000000L // already defined

#define M_NORMALIZATION_SCALE                         2856L
#define M_NORMALIZATION_OFFSET                        2857L

#define M_UPDATE_TRAINED_CNN_PARAMS                   3706L 

#define M_NOW                                           29L // already defined in mil3ddisp.h

#define M_MOVE_ENTRIES                                4057L

////////////////////////////////////////////////////////////////////////////////
// MclassSplitDataset

#define M_SPLIT_CONTEXT_DEFAULT                     (3979L | M_PSEUDO_ID)  
#define M_SPLIT_CONTEXT_FIXED_SEED                  (3980L | M_PSEUDO_ID)  


#if OldDefinesSupport
#define M_PREDICT_MODE                                2859L
#define M_SINGLE_CLASSIFICATION                       2860L
#define M_CLASSIFICATION_MAP                          2861L
#define M_CLASSIFICATION_MAP_INPUT_SIZE_X             2871L
#define M_CLASSIFICATION_MAP_INPUT_SIZE_Y             2872L
#define M_PRETRAINED_CONVOLUTIONAL_NETWORK            2913L
MIL_DEPRECATED(M_PREDICT_MODE                    , 1040)
MIL_DEPRECATED(M_SINGLE_CLASSIFICATION           , 1040)
MIL_DEPRECATED(M_CLASSIFICATION_MAP              , 1040)
MIL_DEPRECATED(M_CLASSIFICATION_MAP_INPUT_SIZE_X , 1040)
MIL_DEPRECATED(M_CLASSIFICATION_MAP_INPUT_SIZE_Y , 1040)
MIL_DEPRECATED(M_PRETRAINED_CONVOLUTIONAL_NETWORK, 1040)
#endif

#define M_CLASSIFICATION_MAP_SIZE_X                   2862L
#define M_CLASSIFICATION_MAP_SIZE_Y                   2863L

#define M_TARGET_IMAGE_SIZE_X                         3358L
#define M_TARGET_IMAGE_SIZE_Y                         3359L

#define M_OPERATION                                M_METHOD // already defined
#define M_ADD                                       0x0000L // already defined

#define M_CONSTANT                                  0x8000L // already defined

#define M_CLASS_ICON_ID                               2907L

#if OldDefinesSupport
#define M_SAMPLE_IMAGE_ID                             M_CLASS_ICON_ID
MIL_DEPRECATED(M_SAMPLE_IMAGE_ID, 1040)
#endif

#define M_CLASS_WEIGHT                                3612L

#define M_PREDICT_SCORES_HISTOGRAM                    3936L
#define M_PREDICT_SCORES_COMPLEMENTS_HISTOGRAM        3937L
#define M_PREDICT_SCORES_ALL_CLASSES_HISTOGRAM        3938L

#define M_MAX_NUMBER_OF_CLASSES                       2946L 


#if OldDefinesSupport
#define M_NUMBER_OF_CLASS_DEFINITIONS                 M_NUMBER_OF_CLASSES
#define M_MAX_NUMBER_OF_CLASS_DESCRIPTIONS            M_MAX_NUMBER_OF_CLASSES
#define M_MAX_NUMBER_OF_CLASS_DEFINITIONS             M_MAX_NUMBER_OF_CLASSES
MIL_DEPRECATED(M_NUMBER_OF_CLASS_DEFINITIONS, 1040)
MIL_DEPRECATED(M_MAX_NUMBER_OF_CLASS_DEFINITIONS, 1040)
MIL_DEPRECATED(M_MAX_NUMBER_OF_CLASS_DESCRIPTIONS, 1040)
#endif



#define M_MP_USE                                      (M_APP_INQUIRE_SYS_START+128L) // 15128 (already defined)




#define M_CNN_TRAIN_ENGINE                            3426L
#define M_CPU                                         3427L
#define M_CNN_TRAIN_ENGINE_USED                       3800L


#define M_CNN_TRAIN_ENGINE_USED_DESCRIPTION           (6272L | M_CLIENT_ENCODING)

#define M_CNN_TRAIN_ENGINE_IS_INSTALLED               3768L
#define M_TRAINED_CNN_PARAMETERS_UPDATED              3775L

#define M_CLASSIFIER_STATUS                           3781L
#define M_PRETRAINED                                  3782L
#define M_USER_TRAINED                                3783L

#define M_UNDEFINED                                   3948L
#define M_UNTRAINED                                   3733L 

#define M_CLASSIFIER_CNN_PREDEFINED_TYPE              3978L

// Result
#define M_RESET                                          9L // already defined

#define M_NUMBER_OF_TREES                             3515L 
#define M_SEED_VALUE                                  2867L  //  already defined in milim.h
#define M_SEED_MODE                                   3863L 
#define M_AUTO                                         444L  //  already defined in mil.h
#define M_USER_DEFINED_SEED                           3465L  //  already defined in milim.h 

#define M_NODE_MAX_NUMBER_OF_FEATURES_MODE            3516L 
#define M_NUMBER_OF_FEATURES                          1002L //  already defined in milmetrol.h
#define M_FEATURE_IMPORTANCE_MODE                     3613L  
#define M_MEAN_DECREASE_IMPURITY                      3614L  
#define M_PERMUTATION                                 3615L 
#define M_DROP_COLUMN                                 3966L //  already defined in mildb.h

#define M_VALUE                                           0L  // already defined in milim.h
#define M_PERCENTAGE                                      2L  // already defined in milim.h
#define M_SQUARE_ROOT                                 M_SQRT  // already defined in milim.h
#define M_LOG2                                       0x0107L  // already defined in milim.h
#define M_ALL                                    0x40000000L  // already defined in mil.h

#define M_USER_DEFINED_VALUE                           3942L
#define M_USER_DEFINED_PERCENTAGE                      3943L

#define M_NODE_MAX_NUMBER_OF_FEATURES                  3517L
#define M_BOOTSTRAP                                    3518L

#define M_TREE_MAX_DEPTH                               3318  // already definded in mil3dmap.h
#define M_NONE                                   0x08000000L // already defines in milim.h

#define M_TREE_MAX_NUMBER_OF_LEAF_NODES                3780L
#define M_MIN_NUMBER_OF_ENTRIES_SPLIT_MODE             3519L
#define M_MIN_NUMBER_OF_ENTRIES_SPLIT                  3522L

#define M_MIN_WEIGHT_FRACTION_LEAF                     3523L  

#define M_MIN_NUMBER_OF_ENTRIES_LEAF_MODE              3524L 
#define M_MIN_NUMBER_OF_ENTRIES_LEAF                   3525L

#define M_OUT_OF_BAG_ACCURACY                          3804L  
#define M_OUT_OF_BAG_ERROR_RATE                        3526L 
#define M_COMPUTE_OUT_OF_BAG_RESULTS                   3527L  

#define M_FORMAT_DOT                                   3864L

#define M_MIN_IMPURITY_DECREASE                        3528L  

#define M_CLASS_WEIGHT_MODE                            3529L  

#define M_SORT                                         0x00200000L // already defined in milocr.h

#define M_FEATURE_IMPORTANCE_SET                       3703L
#define M_DEV_DATASET                                  3704L
#define M_OUT_OF_BAG                                   3705L

#define M_BALANCE                                      1483L // already defined in milcolor.h

#define M_TRAIN_DATASET_ERROR_RATE_AFTER_EACH_TREE     3779L
#define M_DEV_DATASET_ERROR_RATE_AFTER_EACH_TREE       3806L
#define M_OUT_OF_BAG_ERROR_RATE_AFTER_EACH_TREE        3530L 

#define M_TRAIN_DATASET_ACCURACY_AFTER_EACH_TREE       3807L
#define M_DEV_DATASET_ACCURACY_AFTER_EACH_TREE         3808L
#define M_OUT_OF_BAG_ACCURACY_AFTER_EACH_TREE          3809L

#define M_SPLIT_QUALITY_TYPE                           3531L
#define M_GINI                                         3532L
#define M_ENTROPY                                      3533L

#define M_COMPUTE_PROXIMITY_MATRIX                     3513L
#define M_PROXIMITY_MATRIX                             3792L
#define M_PROXIMITY_MATRIX_SIZE_X                      3791L
#define M_PROXIMITY_MATRIX_SIZE_Y                      3981L
#define M_OUT_OF_BAG_CONFUSION_MATRIX                  3789L

#define M_TRAIN_REPORT                                 3944L
#define M_TRAIN_TREE                                   3788L 


#define M_WITH_REPLACEMENT                             3786L  
#define M_WITHOUT_REPLACEMENT                          3785L   

#define M_MAX_EPOCH                                    3479L
#define M_MINI_BATCH_SIZE                              3480L

#define M_SCHEDULER_TYPE                               3492L

#define M_INITIAL_LEARNING_RATE                        3493L
#define M_LEARNING_RATE_DECAY                          3494L


#define M_TRANSFER_LEARNING                            3625L 
#define M_FINE_TUNING                                  3626L


////////////////////////////////////////////////////////////////////////////////
// MclassInquire 
// Context
#define M_PREPROCESSED                                  14L // already defined
#define M_INVALID                                        -1 // already defined
#define M_NUMBER_OF_ENTRIES                             24L
#define M_NUMBER_OF_ENTRIES_GROUND_TRUTH              3761L
#define M_NUMBER_OF_ENTRIES_PREDICTED                 3762L
#define M_PREDICTED_SCORE_MIN                         3763L
#define M_PREDICTED_SCORE_MAX                         3764L
#define M_PREDICTED_SCORE_AVERAGE                     3765L
#define M_CONFUSION_MATRIX_ENTRIES                    3939L
#define M_CONFUSION_MATRIX_PERCENTAGE                 3940L
#define M_NUMBER_OF_AUGMENTED_ENTRIES                 3976L
#define M_ACCURACY                                     106L // already defined
#define M_PRECISION                                   1482L // already defined
#define M_GPU_TRAIN_ENGINE_LOAD_STATUS                4110L
#define M_CPU_TRAIN_ENGINE_LOAD_STATUS                4108L

////////////////////////////////////////////////////////////////////////////////
// MclassInquire returned values for M_GPU_TRAIN_ENGINE_LOAD_STATUS and M_CPU_TRAIN_ENGINE_LOAD_STATUS

#define M_SUCCESS                               0x00000000L // already defined
#define M_FAILURE                               0x00000001L // already defined
#define M_JIT_COMPILATION_REQUIRED                    4102L
#define M_JIT_COMPILER_NOT_FOUND                      4100L
#define M_CUDA_FAIL                                   4098L
#define M_UNABLE_TO_FIND_VALID_GPU                    4091L
#define M_UNABLE_TO_LOAD_GPU_TRAIN_ENGINE             4090L
#define M_UNABLE_TO_LOAD_CPU_TRAIN_ENGINE             4089L
#define M_UNABLE_TO_FIND_GPU_TRAIN_ENGINE             4088L
#define M_UNABLE_TO_FIND_CPU_TRAIN_ENGINE             4072L

////////////////////////////////////////////////////////////////////////////////
// MclassName operations

#define M_SET_NAME                                      1L  // also in milmetrol.h
#define M_GET_NAME                                      2L  // also in milmetrol.h


#define M_LAST_LAYER_SOFTMAX                    0x00040000L                         

////////////////////////////////////////////////////////////////////////////////
// MclassGetResult ResultTypes

#define M_STATUS                                0x00008002L // already defined
#define M_TIMEOUT_REACHED                             2554L
#define M_STOPPED_BY_REQUEST                          2555L
#define M_NOT_ENOUGH_MEMORY                              4L // already defined
#define M_NOT_ENOUGH_GPU_MEMORY                     958494L
#define M_NON_FINITE_VALUE_DETECTED                   4746L
#define M_COMPLETE                              0x00000000L // already defined
#define M_INTERNAL_ERROR                                 5L // already defined
#define M_PREDICT_NOT_PERFORMED                       2788L
#define M_CURRENTLY_PREDICTING                        2789L
#define M_TRAINING_NOT_PERFORMED                      3424L
#define M_CURRENTLY_TRAINING                          3425L
#define M_IMAGE_FILE_NOT_FOUND                        3793L
#define M_INVALID_NUMBER_OF_FEATURES                  3951L

#define M_NUMBER_OF_CLASSES                           2848L
#define M_CLASS_SCORES                                2837L 
#define M_BEST_CLASS_INDEX                            2847L
#define M_BEST_CLASS_SCORE                            2889L
#define M_NUMBER_OF_CLASS_SCORES                      2864L
#define M_CLASS_MAP_INDEX_IMAGE_TYPE                  3355L
#define M_RECEPTIVE_FIELD_SIZE_X                      3379L
#define M_RECEPTIVE_FIELD_SIZE_Y                      3380L
#define M_CLASSIFICATION_MAP_SCALE_X                  3332L
#define M_CLASSIFICATION_MAP_SCALE_Y                  3333L
#define M_CLASSIFICATION_MAP_OFFSET_X                 3334L
#define M_CLASSIFICATION_MAP_OFFSET_Y                 3335L
#define M_FEATURE_IMPORTANCE                          3534L   
#define M_NUMBER_OF_ENTRIES_OUT_OF_BAG                3535L  
#define M_TREE_DEPTHS_ACHIEVED                        3536L  
#define M_TREE_NUMBER_OF_LEAF_NODES_ACHIEVED          3810L   
#define M_TREE_DEPTH_ACHIEVED                         3811L  
#define M_NUMBER_OF_TREES_TRAINED                     3813L   
#define M_TRAIN_IMAGE_MIN_SIZE_X                      3729L
#define M_TRAIN_IMAGE_MIN_SIZE_Y                      3730L
#define M_TRAIN_IMAGE_STEP_X                          3731L
#define M_TRAIN_IMAGE_STEP_Y                          3732L
#define M_TRAINABLE_COMPLETE                          3949L
#define M_TRAINABLE_TRANSFER_LEARNING                 3974L
#define M_TRAINABLE_FINE_TUNING                       3975L

#define M_DEV_DATASET_ACCURACY                        3555L
#define M_TRAIN_DATASET_ACCURACY                      3556L
#define M_DEV_DATASET_EPOCH_ACCURACY                  3642L
#define M_TRAIN_DATASET_MINI_BATCH_LOSS               3643L
#define M_TRAIN_DATASET_EPOCH_ACCURACY                3727L
#define M_MINI_BATCH_PER_EPOCH                        3737L
#define M_DEV_DATASET_ERROR_RATE                      3745L
#define M_TRAIN_DATASET_ERROR_RATE                    3746L
#define M_DEV_DATASET_EPOCH_ERROR_RATE                3747L
#define M_TRAIN_DATASET_EPOCH_ERROR_RATE              3748L
#define M_LAST_EPOCH_UPDATED_PARAMETERS               3839L

#define M_TRAIN_DATASET_CONFUSION_MATRIX              3608L
#define M_TRAIN_DATASET_CONFUSION_MATRIX_SIZE_X       3609L
#define M_TRAIN_DATASET_CONFUSION_MATRIX_SIZE_Y       3982L
#define M_DEV_DATASET_CONFUSION_MATRIX                3610L
#define M_DEV_DATASET_CONFUSION_MATRIX_SIZE_X         3611L
#define M_DEV_DATASET_CONFUSION_MATRIX_SIZE_Y         3983L
#define M_OUT_OF_BAG_CONFUSION_MATRIX_SIZE_X          3805L
#define M_OUT_OF_BAG_CONFUSION_MATRIX_SIZE_Y          3984L
#define M_TRAIN_DATASET_USED_ENTRIES                  3985L
#define M_DEV_DATASET_USED_ENTRIES                    3986L

////////////////////////////////////////////////////////////////////////////////    
// MclassDraw ControlTypes
#define M_DRAW_CLASS_ICON                             3955L                        
#define M_DRAW_BEST_INDEX_CONTOUR_IMAGE               3356L
#define M_DRAW_CLASS_COLOR_LUT                        4099L
#define M_DRAW_BEST_INDEX_IMAGE                       4101L
#define M_DRAW_BEST_SCORE_IMAGE                       4103L
#define M_DRAW_CLASSIFICATION_SCORE                   4109L
#define M_CLASSIFICATION_MAP_SIZE                     0x2000L
#define M_PSEUDO_COLOR                                0x4000L
#define M_REPLICATE_BORDER                            0x8000L
#define M_RECEPTIVE_FIELD_PATCH                       3752L
#define M_BILINEAR_INTERPOLATION                      M_BILINEAR

////////////////////////////////////////////////////////////////////////////////
// MclassCopyResult options
#define M_TRAINED_CLASSIFIER_CNN                      3640L
#define M_TRAINED_TREE_ENSEMBLE                       3695L 
#define M_TRAIN_DATASET_PREDICT_SCORES                3952L
#define M_DEV_DATASET_PREDICT_SCORES                  3953L  
#define M_OUT_OF_BAG_PREDICT_SCORES                   3965L 

////////////////////////////////////////////////////////////////////////////////    
// MclassHookFunction options
#define M_EPOCH_TRAINED          (M_OBJ_HOOK_MODULE_RANGE_START + 0x01L)
#define M_MINI_BATCH_TRAINED     (M_OBJ_HOOK_MODULE_RANGE_START + 0x02L)
#define M_PREDICT_ENTRY          (M_OBJ_HOOK_MODULE_RANGE_START + 0x05L)

#define M_TREE_TRAINED           (M_OBJ_HOOK_MODULE_RANGE_START + 0x06L) 

////////////////////////////////////////////////////////////////////////////////    
// MclassGetHookInfo options
#define M_EPOCH_INDEX                                 3678L
#define M_MINI_BATCH_INDEX                            3679L
#define M_MINI_BATCH_LOSS                             3680L

#define M_INPUT_DATASET_ID                            3681L 
#define M_OUTPUT_DATASET_ID                           3682L 
#define M_PREDICT_CONTEXT_ID                          3683L 
#define M_PREDICT_SCORE                               3684L 
#define M_PREDICT_SCORE_MIN                           3685L 
#define M_PREDICT_SCORE_MAX                           3686L 
#define M_PREDICT_SCORE_AVERAGE                       3687L 
#define M_NUMBER_OF_PREDICTED_ENTRIES                 3688L 
#define M_NUMBER_OF_ENTRIES_IN_ERROR                  3689L 

#define M_RESULT_ID                                   3691L
#define M_TRAIN_CONTEXT_ID                            3692L
#define M_TRAIN_DATASET_ID                            3693L
#define M_DEV_DATASET_ID                              3694L
#define M_DEV_DATASET_EPOCH_ERROR_ENTRIES             3723L 
#define M_TRAIN_DATASET_EPOCH_ERROR_ENTRIES           3724L 
#define M_DEV_DATASET_ERROR_ENTRIES                   3725L
#define M_TRAIN_DATASET_ERROR_ENTRIES                 3726L

#define M_TREE_INDEX                                  3803L

////////////////////////////////////////////////////////////////////////////////
// CAPI function prototypes
MIL_CLASS_DLLFUNC MIL_ID MFTYPE MclassAlloc(MIL_ID    SysId,
                                            MIL_INT64 ContextType,
                                            MIL_INT64 ControlFlag,
                                            MIL_ID*   ContextClassIdPtr);

MIL_CLASS_DLLFUNC MIL_ID MFTYPE MclassAllocResult(MIL_ID    SysId,
                                                  MIL_INT64 ResultType,
                                                  MIL_INT64 ControlFlag,
                                                  MIL_ID*   ResultClassIdPtr);

MIL_CLASS_DLLFUNC void MFTYPE MclassFree(MIL_ID ClassObjectId);

MIL_CLASS_DLLFUNC void MFTYPE MclassControlMilUuid(MIL_ID     ContextOrResultClassId,
                                                   MIL_INT64  LabelOrIndex,
                                                   MIL_INT64  ControlType,
                                                   MIL_UUID   ControlValue);

MIL_CLASS_DLLFUNC void MFTYPE MclassControlEntryMilUuid(MIL_ID      DatasetContextClassId,
                                                        MIL_INT64   EntryIndex,
                                                        MIL_UUID    EntryKey,
                                                        MIL_INT64   RegionIndex,
                                                        MIL_INT64   ControlType,
                                                        MIL_UUID    ControlValue,
                                                        const void* ControlValuePtr,
                                                        MIL_INT     ControlValuePtrSize);

#if M_MIL_USE_64BIT
// Prototypes for 64 bits OSs
MIL_CLASS_DLLFUNC void MFTYPE MclassControlInt64(MIL_ID     ContextOrResultClassId,
                                                 MIL_INT64  LabelOrIndex,
                                                 MIL_INT64  ControlType,
                                                 MIL_INT64  ControlValue);
MIL_CLASS_DLLFUNC void MFTYPE MclassControlDouble(MIL_ID     ContextOrResultClassId,
                                                  MIL_INT64  LabelOrIndex,
                                                  MIL_INT64  ControlType,
                                                  MIL_DOUBLE ControlValue);

MIL_CLASS_DLLFUNC void MFTYPE MclassControlEntryInt64(MIL_ID      DatasetContextClassId,
                                                      MIL_INT64   EntryIndex,
                                                      MIL_UUID    EntryKey,
                                                      MIL_INT64   RegionIndex,
                                                      MIL_INT64   ControlType,
                                                      MIL_INT64   ControlValue,
                                                      const void* ControlValuePtr,
                                                      MIL_INT     ControlValuePtrSize);

MIL_CLASS_DLLFUNC void MFTYPE MclassControlEntryDouble(MIL_ID      DatasetContextClassId,
                                                       MIL_INT64   EntryIndex,
                                                       MIL_UUID    EntryKey,
                                                       MIL_INT64   RegionIndex,
                                                       MIL_INT64   ControlType,
                                                       MIL_DOUBLE  ControlValue,
                                                       const void* ControlValuePtr,
                                                       MIL_INT     ControlValuePtrSize);
#else
// Prototypes for 32 bits OSs
#define MclassControlInt64  MclassControl
#define MclassControlDouble MclassControl

#define MclassControlEntryInt64  MclassControlEntry
#define MclassControlEntryDouble MclassControlEntry

MIL_CLASS_DLLFUNC void MFTYPE MclassControl(MIL_ID     ContextOrResultClassId,
                                            MIL_INT64  LabelOrIndex,
                                            MIL_INT64  ControlType,
                                            MIL_DOUBLE ControlValue);

MIL_CLASS_DLLFUNC void MFTYPE MclassControlEntry(MIL_ID      DatasetContextClassId,
                                                 MIL_INT64   EntryIndex,
                                                 MIL_UUID    EntryKey,
                                                 MIL_INT64   RegionIndex,
                                                 MIL_INT64   ControlType,
                                                 MIL_DOUBLE  ControlValue,
                                                 const void* ControlValuePtr,
                                                 MIL_INT     ControlValuePtrSize);
#endif

MIL_CLASS_DLLFUNC MIL_INT MFTYPE MclassInquire(MIL_ID    ContextOrResultClassId,
                                               MIL_INT64 LabelOrIndex,
                                               MIL_INT64 InquireType,
                                               void*     UserVarPtr);

MIL_CLASS_DLLFUNC MIL_INT MFTYPE MclassInquireEntry(MIL_ID    DatasetContextClassId,
                                                    MIL_INT64 EntryIndex,
                                                    MIL_UUID  EntryKey,
                                                    MIL_INT64 RegionIndex,
                                                    MIL_INT64 InquireType,
                                                    void*     UserVarPtr);

MIL_CLASS_DLLFUNC void MFTYPE MclassPreprocess(MIL_ID    ContextClassId,
                                               MIL_INT64 ControlFlag);

MIL_CLASS_DLLFUNC void MFTYPE MclassPredict(MIL_ID    ContextClassId,
                                            MIL_ID    TargetMilObjectId,
                                            MIL_ID    DatasetContextOrResultClassId,
                                            MIL_INT64 ControlFlag);

MIL_CLASS_DLLFUNC void MFTYPE MclassPredictMultiBand(MIL_ID        ContextClassId,
                                                     const MIL_ID* TargetImageBufId,
                                                     MIL_INT       NbTargetImages,
                                                     MIL_ID        ResultClassId,
                                                     MIL_INT64     ControlFlag);

MIL_CLASS_DLLFUNC void MFTYPE MclassGetResult(MIL_ID    ResultClassId,
                                              MIL_INT64 LabelOrIndex,
                                              MIL_INT64 ResultType,
                                              void*     ResultArrayPtr);

MIL_CLASS_DLLFUNC void MFTYPE MclassTrain(MIL_ID      TrainContextClassId,
                                          MIL_ID      ClassifierContextClassId,
                                          MIL_ID      TrainDatasetContextClassId,
                                          MIL_ID      DevDatasetContextClassId,
                                          MIL_ID      TrainResultClassId,
                                          MIL_INT64   ControlFlag);

MIL_CLASS_DLLFUNC void MFTYPE MclassDraw(MIL_ID    ContextGraId,
                                         MIL_ID    ContextOrResultClassId,
                                         MIL_ID    DstImageBufOrListGraId,
                                         MIL_INT64 Operation,
                                         MIL_INT64 Index,
                                         MIL_INT64 ControlFlag);

MIL_CLASS_DLLFUNC void MFTYPE MclassCopy(MIL_ID     SrcContextClassId,
                                         MIL_INT64  SrcIndex,
                                         MIL_ID     DstContextClassId,
                                         MIL_INT64  DstIndex,
                                         MIL_INT64  CopyType,
                                         MIL_INT64  ControlFlag);

MIL_CLASS_DLLFUNC void MFTYPE MclassCopyResult(
                                         MIL_ID     SrcResultClassId,
                                         MIL_INT64  SrcIndex,
                                         MIL_ID     DstContextClassId,
                                         MIL_INT64  DstIndex,
                                         MIL_INT64  CopyType,
                                         MIL_INT64  ControlFlag);

MIL_CLASS_DLLFUNC void MFTYPE MclassHookFunction(
                                          MIL_ID                      ClassifierOrTrainingContextId,
                                          MIL_INT64                   HookType,
                                          MIL_CLASS_HOOK_FUNCTION_PTR HookHandlerPtr,
                                          void*                       UserDataPtr);

MIL_CLASS_DLLFUNC MIL_INT MFTYPE MclassGetHookInfo(
                                          MIL_ID    EventId,
                                          MIL_INT64 InfoType,
                                          void*     UserVarPtr);

MIL_CLASS_DLLFUNC void MFTYPE MclassSplitDataset(MIL_ID     SplitContextClassId,
                                                 MIL_ID     SrcDatasetContextClassId,
                                                 MIL_ID     DstFirstDatasetContextClassId,
                                                 MIL_ID     DstSecondDatasetContextClassId,
                                                 MIL_DOUBLE Percentage,
                                                 MIL_ID     SplitResultClassId,
                                                 MIL_INT64  ControlFlag);

#if M_MIL_USE_UNICODE

MIL_CLASS_DLLFUNC void MFTYPE MclassSaveA(MIL_CONST_TEXTA_PTR FileName,
                                          MIL_ID      ContextClassId,
                                          MIL_INT64   ControlFlag);

MIL_CLASS_DLLFUNC MIL_ID MFTYPE MclassRestoreA(MIL_CONST_TEXTA_PTR FileName,
                                               MIL_ID      SysId,
                                               MIL_INT64   ControlFlag,
                                               MIL_ID*     ContextClassIdPtr);

MIL_CLASS_DLLFUNC void MFTYPE MclassStreamA(MIL_TEXTA_PTR MemPtrOrFileName,
                                            MIL_ID     SysId,
                                            MIL_INT64  Operation,
                                            MIL_INT64  StreamType,
                                            MIL_DOUBLE Version,
                                            MIL_INT64  ControlFlag,
                                            MIL_ID*    ContextClassIdPtr,
                                            MIL_INT*   SizeByteVarPtr);

MIL_CLASS_DLLFUNC void MFTYPE MclassImportA(MIL_CONST_TEXTA_PTR FileName,
                                            MIL_INT64           FileFormat,
                                            MIL_ID              DatasetContextClassId,
                                            MIL_INT64           Index,
                                            MIL_INT64           ImportType,
                                            MIL_INT64           ControlFlag);

MIL_CLASS_DLLFUNC void MFTYPE MclassExportA(MIL_CONST_TEXTA_PTR FileName,    
                                            MIL_INT64           FileFormat,  
                                            MIL_ID              DatasetContextOrResultClassId,
                                            MIL_INT64           Index,
                                            MIL_INT64           ExportType,        
                                            MIL_INT64           ControlFlag);



MIL_CLASS_DLLFUNC void MFTYPE MclassSaveW(MIL_CONST_TEXTW_PTR FileName,
                                          MIL_ID              ContextClassId,
                                          MIL_INT64           ControlFlag);

MIL_CLASS_DLLFUNC MIL_ID MFTYPE MclassRestoreW(MIL_CONST_TEXTW_PTR FileName,
                                               MIL_ID              SysId,
                                               MIL_INT64           ControlFlag,
                                               MIL_ID*             ContextClassIdPtr);

MIL_CLASS_DLLFUNC void MFTYPE MclassStreamW(MIL_TEXTW_PTR MemPtrOrFileName,
                                            MIL_ID        SysId,
                                            MIL_INT64     Operation,
                                            MIL_INT64     StreamType,
                                            MIL_DOUBLE    Version,
                                            MIL_INT64     ControlFlag,
                                            MIL_ID*       ContextClassIdPtr,
                                            MIL_INT*      SizeByteVarPtr);

MIL_CLASS_DLLFUNC void MFTYPE MclassImportW(MIL_CONST_TEXTW_PTR FileName,
                                            MIL_INT64           FileFormat,
                                            MIL_ID              DatasetContextClassId,
                                            MIL_INT64           Index,
                                            MIL_INT64           ImportType,
                                            MIL_INT64           ControlFlag);

MIL_CLASS_DLLFUNC void MFTYPE MclassExportW(MIL_CONST_TEXTW_PTR FileName,
                                            MIL_INT64           FileFormat,
                                            MIL_ID              DatasetContextOrResultClassId,
                                            MIL_INT64           Index,
                                            MIL_INT64           ExportType,
                                            MIL_INT64           ControlFlag);





#if M_MIL_UNICODE_API
#define MclassSave               MclassSaveW
#define MclassRestore            MclassRestoreW
#define MclassStream             MclassStreamW
#define MclassImport             MclassImportW                 
#define MclassExport             MclassExportW
#else
#define MclassSave               MclassSaveA
#define MclassRestore            MclassRestoreA
#define MclassStream             MclassStreamA
#define MclassImport             MclassImportA                 
#define MclassExport             MclassExportA
#endif

#else

MIL_CLASS_DLLFUNC void MFTYPE MclassSave(MIL_CONST_TEXT_PTR FileName,
                                         MIL_ID             ContextClassId,
                                         MIL_INT64          ControlFlag);

MIL_CLASS_DLLFUNC MIL_ID MFTYPE MclassRestore(MIL_CONST_TEXT_PTR FileName,
                                              MIL_ID             SysId,
                                              MIL_INT64          ControlFlag,
                                              MIL_ID*            ContextClassIdPtr);

MIL_CLASS_DLLFUNC void MFTYPE MclassStream(MIL_TEXT_PTR MemPtrOrFileName,
                                           MIL_ID       SysId,
                                           MIL_INT64    Operation,
                                           MIL_INT64    StreamType,
                                           MIL_DOUBLE   Version,
                                           MIL_INT64    ControlFlag,
                                           MIL_ID*      ContextClassIdPtr,
                                           MIL_INT*     SizeByteVarPtr);

MIL_CLASS_DLLFUNC void MFTYPE MclassImport(MIL_CONST_TEXT_PTR  FileName,
                                           MIL_INT64           FileFormat,
                                           MIL_ID              DatasetContextClassId,
                                           MIL_INT64           Index,
                                           MIL_INT64           ImportType,
                                           MIL_INT64           ControlFlag); 

MIL_CLASS_DLLFUNC void MFTYPE MclassExport(MIL_CONST_TEXT_PTR  FileName,
                                           MIL_INT64           FileFormat,
                                           MIL_ID              DatasetContextOrResultClassId,
                                           MIL_INT64           Index,
                                           MIL_INT64           ExportType,
                                           MIL_INT64           ControlFlag);




#endif



   /* C++ directive if needed */
#ifdef __cplusplus
   }
#endif
////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

inline void MFTYPE MclassStreamCpp(MilStreamParam MemPtrOrFileName,
                                   MIL_ID         SysId,
                                   MIL_INT64      Operation,
                                   MIL_INT64      StreamType,
                                   MIL_DOUBLE     Version,
                                   MIL_INT64      ControlFlag,
                                   MIL_ID*        ContextClassIdPtr,
                                   MIL_INT*       SizeByteVarPtr)
   {
   MclassStream(MemPtrOrFileName.m_Param, SysId, Operation, StreamType, Version, ControlFlag, ContextClassIdPtr, SizeByteVarPtr);
   }

#undef  MclassStream
#define MclassStream MclassStreamCpp

// Overload for MIL_UUID as ControlValue
inline void MFTYPE MclassControl(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 ControlType, const MIL_UUID& ControlValue)
   {
   MclassControlMilUuid(ContextOrResultClassId, LabelOrIndex, ControlType, ControlValue);
   }

#if M_MIL_USE_MIL_UNIQUE_ID
// Overload for applicable MIL_UNIQUE_..._IDs.
inline void MclassControl(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 ControlType, const MIL_UNIQUE_BUF_ID& ControlValue)
   {
   MclassControlInt64(ContextOrResultClassId, LabelOrIndex, ControlType, ControlValue.get());
   }
#endif

inline void MFTYPE MclassControlEntry(MIL_ID      DatasetContextClassId,
                                      MIL_INT64   EntryIndex,
                                      MIL_UUID    EntryKey,
                                      MIL_INT64   RegionIndex,
                                      MIL_INT64   ControlType,
                                      MIL_UUID    ControlValue,
                                      const void* ControlValuePtr,
                                      MIL_INT     ControlValuePtrSize)
   {
   MclassControlEntryMilUuid(DatasetContextClassId,
                             EntryIndex,
                             EntryKey,
                             RegionIndex,
                             ControlType,
                             ControlValue,
                             ControlValuePtr,
                             ControlValuePtrSize);
   }

#endif // __cplusplus

#if M_MIL_USE_64BIT
#ifdef __cplusplus

//////////////////////////////////////////////////////////////
// MclassControl function overloads when compiling c++ files
//////////////////////////////////////////////////////////////
inline void MclassControl(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 ControlType, float ControlValue)
   {
   MclassControlDouble(ContextOrResultClassId, LabelOrIndex, ControlType, ControlValue);
   }

inline void MclassControl(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 ControlType, MIL_DOUBLE ControlValue)
   {
   MclassControlDouble(ContextOrResultClassId, LabelOrIndex, ControlType, ControlValue);
   }

template <typename T>
inline void MclassControl(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 ControlType, T* ControlValue)
   {
   MclassControlInt64(ContextOrResultClassId, LabelOrIndex, ControlType, M_PTR_TO_MIL_INT(ControlValue));
   }

template <typename T>
inline void MclassControl(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 ControlType, T ControlValue)
   {
   MclassControlInt64(ContextOrResultClassId, LabelOrIndex, ControlType, (MIL_INT64) ControlValue);
   }

//////////////////////////////////////////////////////////////
// MclassControlEntry function overloads when compiling c++ files
//////////////////////////////////////////////////////////////
template <typename T>
inline void MclassControlEntry(MIL_ID      DatasetContextClassId,
                               MIL_INT64   EntryIndex,
                               MIL_UUID    EntryKey,
                               MIL_INT64   RegionIndex,
                               MIL_INT64   ControlType,
                               T           ControlValue,
                               const void* ControlValuePtr,
                               MIL_INT     ControlValuePtrSize)
   {
   MclassControlEntryInt64(DatasetContextClassId,
                           EntryIndex,
                           EntryKey,
                           RegionIndex,
                           ControlType,
                           ControlValue,
                           ControlValuePtr,
                           ControlValuePtrSize);
   }

inline void MclassControlEntry(MIL_ID      DatasetContextClassId,
                               MIL_INT64   EntryIndex,
                               MIL_UUID    EntryKey,
                               MIL_INT64   RegionIndex,
                               MIL_INT64   ControlType,
                               MIL_DOUBLE  ControlValue,
                               const void* ControlValuePtr,
                               MIL_INT     ControlValuePtrSize)
   {
   MclassControlEntryDouble(DatasetContextClassId,
                            EntryIndex,
                            EntryKey,
                            RegionIndex,
                            ControlType,
                            ControlValue,
                            ControlValuePtr,
                            ControlValuePtrSize);
   }

inline void MclassControlEntry(MIL_ID      DatasetContextClassId,
                               MIL_INT64   EntryIndex,
                               MIL_UUID    EntryKey,
                               MIL_INT64   RegionIndex,
                               MIL_INT64   ControlType,
                               MIL_FLOAT   ControlValue,
                               const void* ControlValuePtr,
                               MIL_INT     ControlValuePtrSize)
   {
   MclassControlEntryDouble(DatasetContextClassId,
                            EntryIndex,
                            EntryKey,
                            RegionIndex,
                            ControlType,
                            ControlValue,
                            ControlValuePtr,
                            ControlValuePtrSize);
   }
#else // __cplusplus

//////////////////////////////////////////////////////////////
// For C file, call the default function, i.e. Double one
//////////////////////////////////////////////////////////////
#define MclassControl            MclassControlDouble
#define MclassControlEntry       MclassControlEntryDouble

#endif // __cplusplus
#endif // M_MIL_USE_64BIT

#if M_MIL_USE_SAFE_TYPE

//////////////////////////////////////////////////////////////
// See milos.h for explanation about these functions.
//////////////////////////////////////////////////////////////

// -------------------------------------------------------------------------
// Utility structures for void pointers.

struct ClassVoidPtr
   {
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
   inline ClassVoidPtr(std::nullptr_t): m_IntVal(M_NULL), m_PtrType(0) {}
#endif
   inline ClassVoidPtr(int         NullPtr     ):  m_IntVal (NullPtr     ), m_PtrType(0) {}
   inline ClassVoidPtr(MIL_UINT8  *MilUInt8Ptr ) : m_VoidPtr(MilUInt8Ptr ), m_PtrType(8  + M_UNSIGNED) {}
   inline ClassVoidPtr(MIL_UINT16 *MilUInt16Ptr) : m_VoidPtr(MilUInt16Ptr), m_PtrType(16 + M_UNSIGNED) {}
   inline ClassVoidPtr(MIL_UINT32 *MilUInt32Ptr) : m_VoidPtr(MilUInt32Ptr), m_PtrType(32 + M_UNSIGNED) {}
   inline ClassVoidPtr(MIL_UINT64 *MilUInt64Ptr) : m_VoidPtr(MilUInt64Ptr), m_PtrType(64 + M_UNSIGNED) {}
   inline ClassVoidPtr(MIL_INT8   *MilInt8Ptr  ) : m_VoidPtr(MilInt8Ptr  ), m_PtrType(8  + M_SIGNED  ) {}
   inline ClassVoidPtr(MIL_INT16  *MilInt16Ptr ) : m_VoidPtr(MilInt16Ptr ), m_PtrType(16 + M_SIGNED  ) {}
   inline ClassVoidPtr(MIL_INT32  *MilInt32Ptr ) : m_VoidPtr(MilInt32Ptr ), m_PtrType(32 + M_SIGNED  ) {}
   inline ClassVoidPtr(MIL_INT64  *MilInt64Ptr ) : m_VoidPtr(MilInt64Ptr ), m_PtrType(64 + M_SIGNED  ) {}
   inline ClassVoidPtr(MIL_FLOAT  *MilFloatPtr ) : m_VoidPtr(MilFloatPtr ), m_PtrType(32 + M_FLOAT   ) {}
   inline ClassVoidPtr(MIL_DOUBLE *MilDoublePtr) : m_VoidPtr(MilDoublePtr), m_PtrType(64 + M_FLOAT   ) {}

   union
      {
      void*   m_VoidPtr;
      MIL_INT m_IntVal;
      };
   MIL_INT64  m_PtrType;
   };

struct ClassConstVoidPtr
   {
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
   inline ClassConstVoidPtr(std::nullptr_t): m_IntVal(M_NULL), m_PtrType(0) {}
#endif
   inline ClassConstVoidPtr(int               NullPtr): m_IntVal(NullPtr), m_PtrType(0) {}
   inline ClassConstVoidPtr(const MIL_UINT8  *MilUInt8Ptr ) : m_ConstVoidPtr(MilUInt8Ptr ), m_PtrType(8  + M_UNSIGNED) {}
   inline ClassConstVoidPtr(const MIL_UINT16 *MilUInt16Ptr) : m_ConstVoidPtr(MilUInt16Ptr), m_PtrType(16 + M_UNSIGNED) {}
   inline ClassConstVoidPtr(const MIL_UINT32 *MilUInt32Ptr) : m_ConstVoidPtr(MilUInt32Ptr), m_PtrType(32 + M_UNSIGNED) {}
   inline ClassConstVoidPtr(const MIL_UINT64 *MilUInt64Ptr) : m_ConstVoidPtr(MilUInt64Ptr), m_PtrType(64 + M_UNSIGNED) {}
   inline ClassConstVoidPtr(const MIL_INT8   *MilInt8Ptr  ) : m_ConstVoidPtr(MilInt8Ptr  ), m_PtrType(8  + M_SIGNED  ) {}
   inline ClassConstVoidPtr(const MIL_INT16  *MilInt16Ptr ) : m_ConstVoidPtr(MilInt16Ptr ), m_PtrType(16 + M_SIGNED  ) {}
   inline ClassConstVoidPtr(const MIL_INT32  *MilInt32Ptr ) : m_ConstVoidPtr(MilInt32Ptr ), m_PtrType(32 + M_SIGNED  ) {}
   inline ClassConstVoidPtr(const MIL_INT64  *MilInt64Ptr ) : m_ConstVoidPtr(MilInt64Ptr ), m_PtrType(64 + M_SIGNED  ) {}
   inline ClassConstVoidPtr(const MIL_FLOAT  *MilFloatPtr ) : m_ConstVoidPtr(MilFloatPtr ), m_PtrType(32 + M_FLOAT   ) {}
   inline ClassConstVoidPtr(const MIL_DOUBLE *MilDoublePtr) : m_ConstVoidPtr(MilDoublePtr), m_PtrType(64 + M_FLOAT   ) {}

   union
      {
      const void* m_ConstVoidPtr;
      MIL_INT     m_IntVal;
      };
   MIL_INT64      m_PtrType;
   };

// -------------------------------------------------------------------------
// MclassGetResult safe type declarations

inline void MFTYPE MclassGetResultUnsafe  (MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, void*          ResultArrayPtr);
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, int            ResultArrayPtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS                                                    
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, std::nullptr_t ResultArrayPtr);
#endif                                                                                        
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_INT8*      ResultArrayPtr);
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_INT16*     ResultArrayPtr);
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_INT32*     ResultArrayPtr);
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_INT64*     ResultArrayPtr);
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, float*         ResultArrayPtr);
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_DOUBLE*    ResultArrayPtr);
#if M_MIL_UNICODE_API                                                    
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_TEXT_PTR   ResultArrayPtr);
#endif                                                                                        
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                                         
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_UINT8*     ResultArrayPtr);
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_UINT16*    ResultArrayPtr);
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_UINT32*    ResultArrayPtr);
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_UINT64*    ResultArrayPtr);
#endif

// -------------------------------------------------------------------------
// MclassGetResult safe type definitions
// 

inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, int ResultPtr)
   {
   if(ResultPtr != 0)
      SafeTypeError(MIL_TEXT("MclassGetResult"));

   MclassGetResult(ResultClassId, LayerLabelOrIndex, ResultType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, std::nullptr_t ResultPtr)
   {
   if(ResultPtr != M_NULL)
      SafeTypeError(MIL_TEXT("MclassGetResult"));

   MclassGetResult(ResultClassId, LayerLabelOrIndex, ResultType, NULL);
   }
#endif


inline void MclassGetResultSafeTypeExecute(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, void* ResultArrayPtr, MIL_INT64 GivenType)
   {
   MIL_INT64 RequiredType = (ResultType & M_HLVLDATATYPE_MASK);
   if((RequiredType != M_TYPE_MIL_DOUBLE) && (RequiredType != M_TYPE_MIL_INT32) && (RequiredType != M_TYPE_MIL_INT64) &&
      (RequiredType != M_TYPE_MIL_ID)     && (RequiredType != M_TYPE_FLOAT)     && (RequiredType != M_TYPE_CHAR)      &&
      (RequiredType != M_TYPE_SHORT)      && (RequiredType != M_TYPE_MIL_UINT8) && (RequiredType != M_TYPE_STRING)    &&
      (RequiredType != M_TYPE_MIL_UUID))
      { RequiredType = 0; }

   bool UuidGetResult = (  (ResultType == M_DEV_DATASET_ERROR_ENTRIES)
                        || (ResultType == M_TRAIN_DATASET_ERROR_ENTRIES)
                        || (ResultType == M_TRAIN_DATASET_USED_ENTRIES)
                        || (ResultType == M_DEV_DATASET_USED_ENTRIES)
                        );
   if(RequiredType == 0)
      {
      RequiredType = (!UuidGetResult) ? M_TYPE_MIL_DOUBLE : M_TYPE_MIL_UUID;
      }

   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if(RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("MclassGetResult"));

   MclassGetResult(ResultClassId, LayerLabelOrIndex, ResultType, ResultArrayPtr);
   }


inline void MFTYPE MclassGetResultUnsafe(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, void*        ResultArrayPtr) { MclassGetResult(ResultClassId, LayerLabelOrIndex, ResultType, ResultArrayPtr); }
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_INT8*    ResultArrayPtr) { MclassGetResultSafeTypeExecute(ResultClassId, LayerLabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_CHAR); }
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_UINT8*   ResultArrayPtr) { MclassGetResultSafeTypeExecute(ResultClassId, LayerLabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_MIL_UINT8); }
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_INT16*   ResultArrayPtr) { MclassGetResultSafeTypeExecute(ResultClassId, LayerLabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_SHORT); }
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_INT32*   ResultArrayPtr) { MclassGetResultSafeTypeExecute(ResultClassId, LayerLabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_MIL_INT32); }
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_INT64*   ResultArrayPtr) { MclassGetResultSafeTypeExecute(ResultClassId, LayerLabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_MIL_INT64); }
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, float*       ResultArrayPtr) { MclassGetResultSafeTypeExecute(ResultClassId, LayerLabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_FLOAT); }
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_DOUBLE*  ResultArrayPtr) { MclassGetResultSafeTypeExecute(ResultClassId, LayerLabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_MIL_DOUBLE); }
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_UUID*    ResultArrayPtr) { MclassGetResultSafeTypeExecute(ResultClassId, LayerLabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_MIL_UUID); }

#if M_MIL_UNICODE_API
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_TEXT_PTR ResultArrayPtr) { MclassGetResultSafeTypeExecute(ResultClassId, LayerLabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_STRING); }
#endif

#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_UINT16* ResultArrayPtr) { MclassGetResultSafeTypeExecute(ResultClassId, LayerLabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_SHORT); }
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_UINT32* ResultArrayPtr) { MclassGetResultSafeTypeExecute(ResultClassId, LayerLabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_MIL_INT32); }
inline void MFTYPE MclassGetResultSafeType(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 ResultType, MIL_UINT64* ResultArrayPtr) { MclassGetResultSafeTypeExecute(ResultClassId, LayerLabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_MIL_INT64); }
#endif

// ----------------------------------------------------------
// MclassInquire safe type declarations

inline MIL_INT MFTYPE MclassInquireUnsafe(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, void*          UserVarPtr);
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, int            UserVarPtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, std::nullptr_t UserVarPtr);
#endif
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_INT8*      UserVarPtr);
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_INT32*     UserVarPtr);
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_INT64*     UserVarPtr);
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, float*         UserVarPtr);
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_DOUBLE*    UserVarPtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                                                        
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_UINT8*     UserVarPtr);
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_UINT16*    UserVarPtr);
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_UINT32*    UserVarPtr);
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_UINT64*    UserVarPtr);
#endif                                                                              
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T                                                     
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID ContextOrResultClassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, wchar_t*    UserVarPtr);
#endif

// ----------------------------------------------------------
// MclassInquireEntry safe type declarations

inline MIL_INT MFTYPE MclassInquireEntryUnsafe  (MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, void*          UserVarPtr);
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, int            UserVarPtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS                                        
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, std::nullptr_t UserVarPtr);
#endif                                                                           
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_INT8*      UserVarPtr);
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_INT32*     UserVarPtr);
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_INT64*     UserVarPtr);
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, float*         UserVarPtr);
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_DOUBLE*    UserVarPtr);
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_UUID*      UserVarPtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                                                      
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_UINT8*     UserVarPtr);
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_UINT16*    UserVarPtr);
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_UINT32*    UserVarPtr);
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_UINT64*    UserVarPtr);
#endif                                                                              
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T                                                     
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, wchar_t*    UserVarPtr);
#endif

// ----------------------------------------------------------
// MclassInquire safe type definitions

inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID MclassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, int UserVarPtr)
   {
   if(UserVarPtr != 0)
      SafeTypeError(MIL_TEXT("MclassInquire"));

   return MclassInquire(MclassId, LabelOrIndex, InquireType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID MclassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, std::nullptr_t)
   {
   return MclassInquire(MclassId, LabelOrIndex, InquireType, NULL);
   }
#endif

inline MIL_INT MFTYPE MclassInquireSafeTypeExecute(MIL_ID MclassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, void* UserVarPtr, MIL_INT64 GivenType)
   {
   MIL_INT64 RequiredType = (InquireType & M_HLVLDATATYPE_MASK);

   if((RequiredType != M_TYPE_MIL_DOUBLE) && (RequiredType != M_TYPE_MIL_INT32) && (RequiredType != M_TYPE_MIL_INT64) &&
      (RequiredType != M_TYPE_MIL_ID) && (RequiredType != M_TYPE_FLOAT) && (RequiredType != M_TYPE_CHAR) &&
      (RequiredType != M_TYPE_SHORT) && (RequiredType != M_TYPE_MIL_UINT8) && (RequiredType != M_TYPE_STRING) &&
      (RequiredType != M_TYPE_MIL_UUID))
      { RequiredType = 0; }

   MIL_INT64 StrippedInquireType = M_STRIP_CLIENT_TEXT_ENCODING(InquireType);
   bool StrInquire = (  (StrippedInquireType == M_STRIP_CLIENT_TEXT_ENCODING(M_EXPIRY_DATE_STRING))
                     || (StrippedInquireType == M_STRIP_CLIENT_TEXT_ENCODING(M_CLASS_NAME))
                     || (StrippedInquireType == M_STRIP_CLIENT_TEXT_ENCODING(M_AUTHOR_NAME))
                     || (StrippedInquireType == M_STRIP_CLIENT_TEXT_ENCODING(M_ROOT_PATH))
                     || (StrippedInquireType == M_STRIP_CLIENT_TEXT_ENCODING(M_CNN_TRAIN_ENGINE_USED_DESCRIPTION))
                     );

   if(RequiredType == 0)
      {
      bool UuidInquire = (  (InquireType == M_CLASS_KEY)
                          ||(InquireType == M_AUTHOR_KEY)
                          );

      RequiredType = (StrInquire ?
                        M_TYPE_STRING :
                        (!UuidInquire) ? M_TYPE_MIL_DOUBLE : M_TYPE_MIL_UUID);
      }

   if(StrInquire                               &&
      M_CLIENT_ASCII_ENCODING_SET(InquireType) &&
      (GivenType == M_TYPE_CHAR))
      {
      GivenType = M_TYPE_STRING;
      }

   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if(RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("MclassInquire"));

   return MclassInquire(MclassId, LabelOrIndex, InquireType, UserVarPtr);
   }

inline MIL_INT MFTYPE MclassInquireUnsafe  (MIL_ID MclassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, void*       UserVarPtr) { return MclassInquire(MclassId, LabelOrIndex, InquireType, UserVarPtr); }
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID MclassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_INT8*   UserVarPtr)
#if M_MIL_UNICODE_API
   { return MclassInquireSafeTypeExecute(MclassId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_CHAR); }
#else
   { return MclassInquireSafeTypeExecute(MclassId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_STRING); }
#endif
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID MclassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_UINT8*  UserVarPtr) { return MclassInquireSafeTypeExecute(MclassId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_MIL_UINT8); }
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID MclassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_INT32*  UserVarPtr) { return MclassInquireSafeTypeExecute(MclassId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_MIL_INT32); }
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID MclassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_INT64*  UserVarPtr) { return MclassInquireSafeTypeExecute(MclassId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_MIL_INT64); }
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID MclassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, float*      UserVarPtr) { return MclassInquireSafeTypeExecute(MclassId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_FLOAT); }
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID MclassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_DOUBLE* UserVarPtr) { return MclassInquireSafeTypeExecute(MclassId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_MIL_DOUBLE); }
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID MclassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_UUID*   UserVarPtr) { return MclassInquireSafeTypeExecute(MclassId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_MIL_UUID); }
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID MclassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_UINT16* UserVarPtr) { return MclassInquireSafeTypeExecute(MclassId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_SHORT); }
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID MclassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_UINT32* UserVarPtr) { return MclassInquireSafeTypeExecute(MclassId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_MIL_INT32); }
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID MclassId, MIL_INT64 LabelOrIndex, MIL_INT64 InquireType, MIL_UINT64* UserVarPtr) { return MclassInquireSafeTypeExecute(MclassId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_MIL_INT64); }
#endif
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T
inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID MclassId, MIL_INT64 LabelOrIndex, MIL_INT64  InquireType, wchar_t*    UserVarPtr) { return MclassInquireSafeTypeExecute(MclassId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_STRING); }
#endif

// ----------------------------------------------------------
// MclassInquireEntry safe type definitions

inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, int UserVarPtr)
   {
   if(UserVarPtr != 0)
      SafeTypeError(MIL_TEXT("MclassInquireEntry"));

   return MclassInquireEntry(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, std::nullptr_t)
   {
   return MclassInquireEntry(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, NULL);
   }
#endif

inline MIL_INT MFTYPE MclassInquireEntrySafeTypeExecute(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, void* UserVarPtr, MIL_INT64 GivenType)
   {
   MIL_INT64 RequiredType = (InquireType & M_HLVLDATATYPE_MASK);

   if((RequiredType != M_TYPE_MIL_DOUBLE) && (RequiredType != M_TYPE_MIL_INT32) && (RequiredType != M_TYPE_MIL_INT64) &&
      (RequiredType != M_TYPE_MIL_ID) && (RequiredType != M_TYPE_FLOAT) && (RequiredType != M_TYPE_CHAR) &&
      (RequiredType != M_TYPE_SHORT) && (RequiredType != M_TYPE_MIL_UINT8) && (RequiredType != M_TYPE_STRING) &&
      (RequiredType != M_TYPE_MIL_UUID))
      { RequiredType = 0; }

   MIL_INT64 StrippedInquireType = M_STRIP_CLIENT_TEXT_ENCODING(InquireType);

   // Default Behaviour if no type is specified. For a MIL_STRING, client should not need to specify + M_TYPE_STRING
   if(RequiredType == 0)
      {
      bool IsMilClassEntryStrControl = (
         StrippedInquireType == M_STRIP_CLIENT_TEXT_ENCODING(M_FILE_PATH)         ||
         StrippedInquireType == M_STRIP_CLIENT_TEXT_ENCODING(M_FILE_PATH_ABS)     ||
         StrippedInquireType == M_STRIP_CLIENT_TEXT_ENCODING(M_ENTRY_USER_STRING) ||
         StrippedInquireType == M_STRIP_CLIENT_TEXT_ENCODING(M_AUTHOR_NAME)
         );
      bool UuidInquire = ((InquireType == M_ENTRY_KEY) ||
                          (InquireType == M_AUGMENTATION_SOURCE_KEY));
      RequiredType = (IsMilClassEntryStrControl ?
                        M_TYPE_STRING :
                        (!UuidInquire) ? M_TYPE_MIL_DOUBLE : M_TYPE_MIL_UUID);
      }

   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if(RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("MclassInquireEntry"));

   //UNREFERENCED_PARAMETER(EntryKey);
   //return MclassInquire(DatasetId, EntryIndex, InquireType, UserVarPtr);
   return MclassInquireEntry(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, UserVarPtr);
   }

inline MIL_INT MFTYPE MclassInquireEntryUnsafe  (MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, void*       UserVarPtr) { return MclassInquireEntry(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, UserVarPtr); }
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_INT8*   UserVarPtr)
#if M_MIL_UNICODE_API
   { return MclassInquireEntrySafeTypeExecute(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, UserVarPtr, M_TYPE_CHAR); }
#else
   { return MclassInquireEntrySafeTypeExecute(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, UserVarPtr, M_TYPE_STRING); }
#endif
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_UINT8*  UserVarPtr) { return MclassInquireEntrySafeTypeExecute(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, UserVarPtr, M_TYPE_MIL_UINT8); }
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_INT32*  UserVarPtr) { return MclassInquireEntrySafeTypeExecute(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, UserVarPtr, M_TYPE_MIL_INT32); }
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_INT64*  UserVarPtr) { return MclassInquireEntrySafeTypeExecute(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, UserVarPtr, M_TYPE_MIL_INT64); }
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, float*      UserVarPtr) { return MclassInquireEntrySafeTypeExecute(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, UserVarPtr, M_TYPE_FLOAT); }
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_DOUBLE* UserVarPtr) { return MclassInquireEntrySafeTypeExecute(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, UserVarPtr, M_TYPE_MIL_DOUBLE); }
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_UUID*   UserVarPtr) { return MclassInquireEntrySafeTypeExecute(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, UserVarPtr, M_TYPE_MIL_UUID); }
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                                                                                                                                                                                                      
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_UINT16* UserVarPtr) { return MclassInquireEntrySafeTypeExecute(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, UserVarPtr, M_TYPE_SHORT); }
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_UINT32* UserVarPtr) { return MclassInquireEntrySafeTypeExecute(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, UserVarPtr, M_TYPE_MIL_INT32); }
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_UINT64* UserVarPtr) { return MclassInquireEntrySafeTypeExecute(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, UserVarPtr, M_TYPE_MIL_INT64); }
#endif                                                                                                                                                                                                                                                      
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T                                                                                                                                                                                                                            
inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64  InquireType, wchar_t*   UserVarPtr) { return MclassInquireEntrySafeTypeExecute(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, UserVarPtr, M_TYPE_STRING); }
#endif


// ----------------------------------------------------------
// MclassGetHookInfo safe type declarations

inline MIL_INT MFTYPE MclassGetHookInfoUnsafe  (MIL_ID  EventId, MIL_INT64  InfoType, void*          UserVarPtr);
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, int            UserVarPtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, std::nullptr_t UserVarPtr);
#endif
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_INT8*      UserVarPtr);
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_INT32*     UserVarPtr);
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_INT64*     UserVarPtr);
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, float*         UserVarPtr);
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_DOUBLE*    UserVarPtr);
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_UUID*      UserVarPtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                       
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_UINT8*     UserVarPtr);
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_UINT16*    UserVarPtr);
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_UINT32*    UserVarPtr);
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_UINT64*    UserVarPtr);
#endif                                                                             
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T                                                    
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, wchar_t*       UserVarPtr);
#endif


// ----------------------------------------------------------
// MclassGetHookInfo safe type definitions

inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID EventId, MIL_INT64 InfoType, int UserVarPtr)
   {
   if(UserVarPtr != 0)
      SafeTypeError(MIL_TEXT("MclassGetHookInfo"));

   return MclassGetHookInfo(EventId, InfoType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID EventId, MIL_INT64 InfoType, std::nullptr_t)
   {
   return MclassGetHookInfo(EventId, InfoType, NULL);
   }
#endif

inline MIL_INT MFTYPE MclassGetHookInfoSafeTypeExecute(MIL_ID EventId, MIL_INT64 InfoType, void* UserVarPtr, MIL_INT64 GivenType)
   {
   MIL_INT64 RequiredType = (InfoType & M_HLVLDATATYPE_MASK);

   if((RequiredType != M_TYPE_MIL_DOUBLE) && (RequiredType != M_TYPE_MIL_INT32) && (RequiredType != M_TYPE_MIL_INT64) &&
      (RequiredType != M_TYPE_MIL_ID) && (RequiredType != M_TYPE_FLOAT) && (RequiredType != M_TYPE_CHAR) &&
      (RequiredType != M_TYPE_SHORT) && (RequiredType != M_TYPE_MIL_UINT8) && (RequiredType != M_TYPE_STRING) &&
      (RequiredType != M_TYPE_MIL_UUID))
      { RequiredType = 0; }

   bool UuidGetResult = ((InfoType == M_DEV_DATASET_EPOCH_ERROR_ENTRIES)
                      || (InfoType == M_TRAIN_DATASET_EPOCH_ERROR_ENTRIES)
                      || (InfoType == M_TRAIN_DATASET_USED_ENTRIES)
                      || (InfoType == M_DEV_DATASET_USED_ENTRIES)
                      || (InfoType == M_ENTRY_KEY));

   if(RequiredType == 0)
      {
      RequiredType = (!UuidGetResult) ? M_TYPE_MIL_DOUBLE : M_TYPE_MIL_UUID;
      }

   MIL_INT64 StrippedInquireType = M_STRIP_CLIENT_TEXT_ENCODING(InfoType);
   bool StrInquire = (  (StrippedInquireType == M_STRIP_CLIENT_TEXT_ENCODING(M_EXPIRY_DATE_STRING) )
                     );
   if(RequiredType == 0)
      {
      RequiredType = (StrInquire ? M_TYPE_STRING : M_TYPE_MIL_DOUBLE);
      }

   if(StrInquire                            &&
      M_CLIENT_ASCII_ENCODING_SET(InfoType) &&
      (GivenType == M_TYPE_CHAR))
      {
      GivenType = M_TYPE_STRING;
      }

   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if(RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("MclassGetHookInfo"));

   return MclassGetHookInfo(EventId, InfoType, UserVarPtr);
   }

inline MIL_INT MFTYPE MclassGetHookInfoUnsafe  (MIL_ID  EventId, MIL_INT64  InfoType, void*       UserVarPtr) { return MclassGetHookInfo               (EventId, InfoType, UserVarPtr                   ); }
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_INT8*   UserVarPtr)
#if M_MIL_UNICODE_API
   { return MclassGetHookInfoSafeTypeExecute(EventId, InfoType, UserVarPtr, M_TYPE_CHAR      ); }
#else
   { return MclassGetHookInfoSafeTypeExecute(EventId, InfoType, UserVarPtr, M_TYPE_STRING); }
#endif
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_UINT8*  UserVarPtr) { return MclassGetHookInfoSafeTypeExecute(EventId, InfoType, UserVarPtr, M_TYPE_MIL_UINT8 ); }
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_INT16*  UserVarPtr) { return MclassGetHookInfoSafeTypeExecute(EventId, InfoType, UserVarPtr, M_TYPE_SHORT     ); }
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_INT32*  UserVarPtr) { return MclassGetHookInfoSafeTypeExecute(EventId, InfoType, UserVarPtr, M_TYPE_MIL_INT32 ); }
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_INT64*  UserVarPtr) { return MclassGetHookInfoSafeTypeExecute(EventId, InfoType, UserVarPtr, M_TYPE_MIL_INT64 ); }
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, float*      UserVarPtr) { return MclassGetHookInfoSafeTypeExecute(EventId, InfoType, UserVarPtr, M_TYPE_FLOAT     ); }
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_DOUBLE* UserVarPtr) { return MclassGetHookInfoSafeTypeExecute(EventId, InfoType, UserVarPtr, M_TYPE_MIL_DOUBLE); }
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_UUID*   UserVarPtr) { return MclassGetHookInfoSafeTypeExecute(EventId, InfoType, UserVarPtr, M_TYPE_MIL_UUID  ); }
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                                                                                                  
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_UINT16* UserVarPtr) { return MclassGetHookInfoSafeTypeExecute(EventId, InfoType, UserVarPtr, M_TYPE_SHORT     ); }
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_UINT32* UserVarPtr) { return MclassGetHookInfoSafeTypeExecute(EventId, InfoType, UserVarPtr, M_TYPE_MIL_INT32 ); }
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, MIL_UINT64* UserVarPtr) { return MclassGetHookInfoSafeTypeExecute(EventId, InfoType, UserVarPtr, M_TYPE_MIL_INT64 ); }
#endif                                                                                                                
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T                                                                                       
inline MIL_INT MFTYPE MclassGetHookInfoSafeType(MIL_ID  EventId, MIL_INT64  InfoType, wchar_t*    UserVarPtr) { return MclassGetHookInfoSafeTypeExecute(EventId, InfoType, UserVarPtr, M_TYPE_STRING    ); }
#endif


//------------------------------
// Safetype functions assignment

#define MclassGetResult            MclassGetResultSafeType
#define MclassInquire              MclassInquireSafeType
#define MclassInquireEntry         MclassInquireEntrySafeType
#define MclassGetHookInfo          MclassGetHookInfoSafeType

#else // #if M_MIL_USE_SAFE_TYPE

#define MclassGetResultUnsafe            MclassGetResult
#define MclassInquireUnsafe              MclassInquire
#define MclassInquireEntryUnsafe         MclassInquireEntry
#define MclassGetHookInfoUnsafe          MclassGetHookInfo
#endif // #if M_MIL_USE_SAFE_TYPE

// ----------------------------------------------------------
// Overload for std::vector.
#if defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR
template <typename UserType>
inline MIL_INT MFTYPE MclassInquire(MIL_ID MclassId, MIL_INT64 LabelOrIndex, MIL_INT64  InquireType, std::vector<UserType> &UserVarPtr)
   {
   // If the given MIL data type is not the same as the SrcType, change it to the correct one
   // and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(InquireType) != 0)
      {
      SafeTypeError(MIL_TEXT("MclassInquire"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   InquireType = M_STRIP_HLVLDATATYPE(InquireType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   MclassInquire(MclassId, LabelOrIndex, M_STRIP_HLVLDATATYPE(InquireType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   UserVarPtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      return MclassInquire(MclassId, LabelOrIndex, InquireType, &UserVarPtr[0]);
      }
   return 0;
   }

template <typename T>
inline void MclassControlEntry(MIL_ID                DatasetContextClassId,
                               MIL_INT64             EntryIndex,
                               MIL_UUID              EntryKey,
                               MIL_INT64             RegionIndex,
                               MIL_INT64             ControlType,
                               MIL_DOUBLE            ControlValue,
                               const std::vector<T>& ControlValues,
                               MIL_INT               ControlValuePtrSize)
   {
   UNREFERENCED_PARAMETER(ControlValuePtrSize);
   MIL_INT NbElements = ControlValues.size();
   if(NbElements == 0)
      return MclassControlEntry(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, ControlType, ControlValue, static_cast<void*>(M_NULL), NbElements);
   else
      return MclassControlEntry(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, ControlType, ControlValue, &ControlValues[0], ControlValues.size());
   }

template <typename UserType>
inline MIL_INT MFTYPE MclassInquireEntry(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64  InquireType, std::vector<UserType> &UserVarPtr)
   {
   // If the given MIL data type is not the same as the SrcType, change it to the correct one
   // and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(InquireType) != 0)
      {
      SafeTypeError(MIL_TEXT("MclassInquireEntry"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   InquireType = M_STRIP_HLVLDATATYPE(InquireType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   MclassInquireEntry(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, M_STRIP_HLVLDATATYPE(InquireType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   UserVarPtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      return MclassInquireEntry(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, &UserVarPtr[0]);
      }
   return 0;
   }

template <typename UserType>
inline void MFTYPE MclassGetResult(MIL_ID ResultClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64  ResultType, std::vector<UserType> &ResultArrayPtr)
   {
   //! If the given MIL data type is not the same as the SrcType, change it to the correct one
   //! and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(ResultType) != 0)
      {
      SafeTypeError(MIL_TEXT("MclassGetResult"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   ResultType = M_STRIP_HLVLDATATYPE(ResultType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   MclassGetResult(ResultClassId, LayerLabelOrIndex, M_STRIP_HLVLDATATYPE(ResultType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   ResultArrayPtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      MclassGetResult(ResultClassId, LayerLabelOrIndex, ResultType, &ResultArrayPtr[0]);
      }
   }

// ----------------------------------------------------------
// Overloads for std::vector in MxxxStream.
inline void MFTYPE MclassStream(std::vector<MIL_UINT8> &MemPtrOrFileName,
                                MIL_ID                 SysId,
                                MIL_INT64              Operation,
                                MIL_INT64              StreamType,
                                MIL_DOUBLE             Version,
                                MIL_INT64              ControlFlag,
                                MIL_ID*                McontextIdPtr,
                                MIL_INT*               SizeByteVarPtr)
   {
   MxxxStreamForStdVector(MemPtrOrFileName,
                          SysId,
                          Operation,
                          StreamType,
                          Version,
                          ControlFlag,
                          McontextIdPtr,
                          SizeByteVarPtr,
                          MclassStream);
   }

// ----------------------------------------------------------
// Overloads for std::vector in MclassPredictMultiBand.
inline  void MFTYPE MclassPredictMultiBand(
   MIL_ID                     ContextId,          //!< [in]
   const std::vector<MIL_ID>& TargetImageArrayPtr,//!< [in]
   MIL_INT                    NbTargetImages,     //!< [in]
   MIL_ID                     ResultId,           //!< [in]
   MIL_INT64                  ControlFlag)        //!< [in]
   {
#if M_MIL_USE_SAFE_TYPE
   if(TargetImageArrayPtr.empty())
      {
      SafeTypeError(MIL_TEXT("MclassPredictMultiBand"), MIL_TEXT("The input vectors cannot be empty."));
      }
   if(NbTargetImages <= 0)
      {
      SafeTypeError(MIL_TEXT("MclassPredictMultiBand"), MIL_TEXT("NbTargetImages parameter must be greater than zero."));
      }
   if(NbTargetImages > (MIL_INT)TargetImageArrayPtr.size() && NbTargetImages != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("MclassPredictMultiBand"), MIL_TEXT("NbTargetImages parameter must be smaller or equal (M_DEFAULT) to the size of input vector."));
      }
#endif

   if(NbTargetImages == M_DEFAULT || NbTargetImages > (MIL_INT)TargetImageArrayPtr.size())
      {
      NbTargetImages = (MIL_INT)TargetImageArrayPtr.size();
      }

   MclassPredictMultiBand(ContextId,
                          &TargetImageArrayPtr[0],
                          NbTargetImages,
                          ResultId,
                          ControlFlag);
   }

// ----------------------------------------------------------
// Overloads for std::vector in MclassGetHookInfo.
template <typename UserType>
inline void MFTYPE MclassGetHookInfo(MIL_ID  EventId, MIL_INT64 InfoType, std::vector<UserType> &ResultArrayPtr)
   {
   //! If the given MIL data type is not the same as the SrcType, change it to the correct one
   //! and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(InfoType) != 0)
      {
      SafeTypeError(MIL_TEXT("MclassGetHookInfo"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   InfoType = M_STRIP_HLVLDATATYPE(InfoType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   MclassGetHookInfo(EventId, M_STRIP_HLVLDATATYPE(InfoType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   ResultArrayPtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      MclassGetHookInfo(EventId, InfoType, &ResultArrayPtr[0]);
      }
   }
#endif // defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR

#if M_MIL_USE_STRING
/***************************************************************************/
/* CLASS MODULE                                                              */
/***************************************************************************/
#if M_MIL_USE_UNICODE
#if M_MIL_UNICODE_API

inline void MFTYPE MclassSaveW(const MIL_STRING& FileName, MIL_ID ContextClassId, MIL_INT64 ControlFlag)
   {
   return MclassSaveW(FileName.c_str(), ContextClassId, ControlFlag);
   }

inline MIL_ID MFTYPE MclassRestoreW(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* ContextClassId)
   {
   return MclassRestoreW(FileName.c_str(), SysId, ControlFlag, ContextClassId);
   }

inline void MFTYPE MclassImportW(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_ID DatasetContextClassId, MIL_INT64 Index, MIL_INT64 ImportType, MIL_INT64 ControlFlag)
   {                                                                                                                                                                    
   MclassImportW(FileName.c_str(), FileFormat, DatasetContextClassId, Index, ImportType, ControlFlag);
   }                                                                                                                                                                    
                                                                                                                                                                       
inline void MFTYPE MclassExportW(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_ID DatasetContextOrResultClassId, MIL_INT64 Index, MIL_INT64 ExportType, MIL_INT64 ControlFlag)
   {                                                                                                                                                                  
   MclassExportW(FileName.c_str(), FileFormat, DatasetContextOrResultClassId, Index, ExportType, ControlFlag);
   }


#else // M_MIL_UNICODE_API
inline void MFTYPE MclassSaveA(const MIL_STRING& FileName, MIL_ID ContextClassId, MIL_INT64 ControlFlag)
   {
   return MclassSaveA(FileName.c_str(), ContextClassId, ControlFlag);
   }

inline MIL_ID MFTYPE MclassRestoreA(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* ContextClassId)
   {
   return MclassRestoreA(FileName.c_str(), SysId, ControlFlag, ContextClassId);
   }

inline void MFTYPE MclassImportA(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_ID DatasetContextClassId, MIL_INT64 Index, MIL_INT64 ImportType, MIL_INT64 ControlFlag)
   {                                                                                                                                                            
   MclassImportA(FileName.c_str(), FileFormat, DatasetContextClassId, Index, ImportType, ControlFlag);
   }                                                                                                                                                                   

inline void MFTYPE MclassExportA(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_ID DatasetContextOrResultClassId, MIL_INT64 Index, MIL_INT64 ExportType, MIL_INT64 ControlFlag)
   {
   MclassExportA(FileName.c_str(), FileFormat, DatasetContextOrResultClassId, Index, ExportType, ControlFlag);
   }


#endif /* M_MIL_UNICODE_API*/


#else // M_MIL_USE_UNICODE
inline void MFTYPE MclassSave(const MIL_STRING& FileName, MIL_ID ContextClassId, MIL_INT64 ControlFlag)
   {
   return MclassSave(FileName.c_str(), ContextClassId, ControlFlag);
   }

inline MIL_ID MFTYPE MclassRestore(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* ContextClassId)
   {
   return MclassRestore(FileName.c_str(), SysId, ControlFlag, ContextClassId);
   }

inline void MFTYPE MclassImport(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_ID DatasetContextClassId, MIL_INT64 Index, MIL_INT64 ImportType, MIL_INT64 ControlFlag)
   {                                                                                                                                                                    
   MclassImport((MIL_CONST_TEXT_PTR)FileName.c_str(), FileFormat, DatasetContextClassId, Index, ImportType, ControlFlag);
   }                                                                                                                                                                    

inline void MFTYPE MclassExport(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_ID DatasetContextOrResultClassId, MIL_INT64 Index, MIL_INT64 ExportType, MIL_INT64 ControlFlag)
   {                                                                                                                                      
   MclassExport((MIL_CONST_TEXT_PTR)FileName.c_str(), FileFormat, DatasetContextOrResultClassId, Index, ExportType, ControlFlag);
   }                                                                                                                                      


#endif /* M_MIL_USE_UNICODE */                                                                                                                                          

inline void MclassControl(MIL_ID ContextClassId, MIL_INT64 LabelOrIndex, MIL_INT64 ControlType, const MIL_STRING& ControlValue)
   {
   MclassControl(ContextClassId, LabelOrIndex, ControlType, M_PTR_TO_MIL_INT(ControlValue.c_str()));
   }

inline void MclassControlEntry(MIL_ID            DatasetContextClassId,
                               MIL_INT64         EntryIndex,
                               MIL_UUID          EntryKey,
                               MIL_INT64         RegionIndex,
                               MIL_INT64         ControlType,
                               MIL_DOUBLE        ControlValue,
                               const MIL_STRING& FileName,
                               MIL_INT           ControlValuePtrSize)
   {
   UNREFERENCED_PARAMETER(ControlValuePtrSize);
   return MclassControlEntry(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, ControlType, static_cast<MIL_DOUBLE>(ControlValue), static_cast<const void*>(FileName.c_str()), (FileName.length() + 1) * sizeof(MIL_TEXT_CHAR));
   }

#if M_MIL_USE_SAFE_TYPE

inline MIL_INT MFTYPE MclassInquireSafeType(MIL_ID ContextClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 InquireType, MIL_STRING &ValuePtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MclassInquire"), MIL_TEXT("Inquire Type not supported with MIL_STRING."));
      }
#endif

   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MclassInquireSafeType(ContextClassId, LayerLabelOrIndex, (InquireType & (~M_HLVLDATATYPE_MASK)) + M_STRING_SIZE + M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ValuePtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MclassInquireSafeTypeExecute(ContextClassId, LayerLabelOrIndex, InquireType, (MIL_TEXT_PTR)ValuePtr.c_str(), M_TYPE_STRING);
      ValuePtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }

inline MIL_INT MFTYPE MclassInquireEntrySafeType(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_STRING &ValuePtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MclassInquireEntry"), MIL_TEXT("Inquire Type not supported with MIL_STRING."));
      }
#endif

   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MclassInquireEntrySafeType(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, (InquireType & (~M_HLVLDATATYPE_MASK)) + M_STRING_SIZE + M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ValuePtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MclassInquireEntrySafeTypeExecute(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, &ValuePtr[0], M_TYPE_STRING);
      ValuePtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }

#else
inline MIL_INT MFTYPE MclassInquire(MIL_ID ContextClassId, MIL_INT64 LayerLabelOrIndex, MIL_INT64 InquireType, MIL_STRING &ValuePtr)
   {
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MclassInquire(ContextClassId, LayerLabelOrIndex, (InquireType & (~M_HLVLDATATYPE_MASK)) + M_STRING_SIZE + M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ValuePtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MclassInquire(ContextClassId, LayerLabelOrIndex, InquireType, &ValuePtr[0]);
      ValuePtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }

inline MIL_INT MFTYPE MclassInquireEntry(MIL_ID DatasetContextClassId, MIL_INT64 EntryIndex, MIL_UUID EntryKey, MIL_INT64 RegionIndex, MIL_INT64 InquireType, MIL_STRING &ValuePtr)
   {
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MclassInquireEntry(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, (InquireType & (~M_HLVLDATATYPE_MASK)) + M_STRING_SIZE + M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ValuePtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MclassInquireEntry(DatasetContextClassId, EntryIndex, EntryKey, RegionIndex, InquireType, &ValuePtr[0]);
      ValuePtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }
#endif
#endif /* M_MIL_USE_STRING*/

////////////////////////////////////////////////////////////////////////////////
// MIL_UNIQUE_ID support

#if M_MIL_USE_MIL_UNIQUE_ID

#if M_MIL_USE_SAFE_TYPE
template <> inline bool MilIsCorrectObjectType<&MclassFree>(MIL_INT64 ObjectType)
   {
   return (ObjectType & ~M_USER_DEFINE_LOW_ATTRIBUTE) == M_CLASS_OBJECT;
   }
#endif

typedef MIL_UNIQUE_ID<&MclassFree> MIL_UNIQUE_CLASS_ID;

#if M_MIL_USE_MOVE_SEMANTICS

inline MIL_UNIQUE_CLASS_ID MclassAlloc(MIL_ID SystemId, MIL_INT64 ContextType, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_CLASS_ID(MclassAlloc(SystemId, ContextType, ControlFlag, M_NULL));
   }
inline MIL_UNIQUE_CLASS_ID MclassAllocResult(MIL_ID SystemId, MIL_INT64 ResultType, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_CLASS_ID(MclassAllocResult(SystemId, ResultType, ControlFlag, M_NULL));
   }
inline MIL_UNIQUE_CLASS_ID MclassRestore(MIL_CONST_TEXT_PTR FileName, MIL_ID SystemId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_CLASS_ID(MclassRestore(FileName, SystemId, ControlFlag, M_NULL));
   }
#if M_MIL_USE_STRING
inline MIL_UNIQUE_CLASS_ID MclassRestore(const MIL_STRING& FileName, MIL_ID SystemId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_CLASS_ID(MclassRestore(FileName, SystemId, ControlFlag, M_NULL));
   }
#endif // M_MIL_USE_STRING
template <MilFreeFuncType FreeFunc> inline void MclassFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

inline void MclassStream(MilStreamParam       MemPtrOrFileName ,
                         MIL_ID               SysId            ,
                         MIL_INT64            Operation        ,
                         MIL_INT64            StreamType       ,
                         MIL_DOUBLE           Version          ,
                         MIL_INT64            ControlFlag      ,
                         MIL_UNIQUE_CLASS_ID* ContextClassIdPtr,
                         MIL_INT*             SizeByteVarPtr   )
   {
   MxxxStreamForMilUniqueId(MemPtrOrFileName, SysId, Operation, StreamType, Version, ControlFlag, ContextClassIdPtr, SizeByteVarPtr, MclassStream);
   }

#endif // M_MIL_USE_MOVE_SEMANTICS
#endif // M_MIL_USE_MIL_UNIQUE_ID

// End of MIL_UNIQUE_ID support
////////////////////////////////////////////////////////////////////////////////

#endif // !M_MIL_LITE
#endif // __MIL_CLASS_H__
