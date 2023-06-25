const router = require("express").Router();
const {
  mainPage,
} = require("../controllers/controller");

module.exports = function () {
  router.get("/", mainPage);
  return router;
};
