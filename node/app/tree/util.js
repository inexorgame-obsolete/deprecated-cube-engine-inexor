const seperator = "/";
const validName = /^[\w ]+$/;

/**
 * @typedef
 * @name datatype
 * @type {treeChildNode|int64|string|float|bool|Date}
 */

/**
 * Checks whether type has a correct {datatype}
 * @name isValidDataType
 * @param {mixed} type
 * @return {bool}
 */
function isValidDataType(datatype) {
    return datatype == "node" || datatype == "int64" || datatype == "string" || datatype == "float" || datatype == "bool" || datatype == "timestamp";
}

module.exports = {
    seperator: seperator,
    validName: validName,
    isValidDataType: isValidDataType
}